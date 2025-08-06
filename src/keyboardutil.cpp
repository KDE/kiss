// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "keyboardutil.h"

#include "initialsystemsetup_debug.h"

#include <KConfig>
#include <KConfigGroup>

#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QTextStream>

KeyboardUtil::KeyboardUtil(QObject *parent)
    : QObject(parent)
{
}

void KeyboardUtil::setLayout(const QString &layout, const QString &variant)
{
    if (m_layout.name == layout && m_layout.variant == variant) {
        return;
    }

    m_layout.name = layout;
    m_layout.variant = variant;
    applyLayout();
}

void KeyboardUtil::applyLayout()
{
    if (m_layout.name.isEmpty()) {
        qCWarning(KDEInitialSystemSetup) << "No keyboard layout set.";
        return;
    }

#ifdef QT_DEBUG
    qCInfo(KDEInitialSystemSetup) << "Skipping actual layout application in debug mode. Would have applied layout:" << m_layout.name
                                  << "with variant:" << m_layout.variant;
    return;
#endif

    qCInfo(KDEInitialSystemSetup) << "Applying keyboard layout:" << m_layout.name << "with variant:" << m_layout.variant;

    applyLayoutForCurrentUser();
    applyLayoutAsSystemDefault();
}

void KeyboardUtil::applyLayoutForCurrentUser()
{
    auto config = new KConfig(QStringLiteral("kxkbrc"), KConfig::NoGlobals);
    KConfigGroup group = config->group(QStringLiteral("Layout"));
    group.writeEntry(QStringLiteral("DisplayNames"), "", KConfig::Notify);
    group.writeEntry(QStringLiteral("LayoutList"), m_layout.name, KConfig::Notify);
    group.writeEntry(QStringLiteral("VariantList"), m_layout.variant, KConfig::Notify);
    config->sync();
    delete config;
}

void KeyboardUtil::applyLayoutAsSystemDefault()
{
    const QString locale1Service = QStringLiteral("org.freedesktop.locale1");
    const QString locale1Path = QStringLiteral("/org/freedesktop/locale1");

    QDBusMessage message = QDBusMessage::createMethodCall( //
        locale1Service,
        locale1Path,
        QStringLiteral("org.freedesktop.locale1"),
        QStringLiteral("SetX11Keyboard") //
    );

    // Default model is hardcoded, since we don't have a way to detect the actual model for now.
    const QString model = QStringLiteral("pc105");
    const QString options = QString();
    // Convert option allows the layout to be applied everywhere with a single command.
    const bool convert = true;
    const bool interactive = false;

    message << m_layout.name << model << m_layout.variant << options << convert << interactive;

    QDBusMessage resultMessage = QDBusConnection::systemBus().call(message);

    if (resultMessage.type() == QDBusMessage::ErrorMessage) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set system default keyboard layout:" << resultMessage.errorMessage();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Successfully set system default keyboard layout.";
    }
}

#include "moc_keyboardutil.cpp"
