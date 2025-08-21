// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "initialsystemsetup_language_debug.h"
#include "languageutil.h"

#include <KLocalizedString>

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusReply>

LanguageUtil::LanguageUtil(QObject *parent)
    : QObject(parent)
{
    loadAvailableLanguages();
    m_currentLanguage = QLocale::system().name();
}

QStringList LanguageUtil::availableLanguages() const
{
    return m_availableLanguages;
}

QString LanguageUtil::currentLanguage() const
{
    return m_currentLanguage;
}

void LanguageUtil::setCurrentLanguage(const QString &language)
{
    if (m_currentLanguage != language) {
        m_currentLanguage = language;
        Q_EMIT currentLanguageChanged();
    }
}

void LanguageUtil::applyLanguage()
{
    if (m_currentLanguage.isEmpty()) {
        return;
    }

    applyLanguageForCurrentSession();
    applyLanguageAsSystemDefault();

    Q_EMIT currentLanguageChanged();
}

void LanguageUtil::applyLanguageForCurrentSession()
{
    qputenv("LANGUAGE", m_currentLanguage.toUtf8());
    qputenv("LANG", m_currentLanguage.toUtf8());
    QLocale::setDefault(QLocale(m_currentLanguage));

    QEvent localeChangeEvent(QEvent::LocaleChange);
    QCoreApplication::sendEvent(QCoreApplication::instance(), &localeChangeEvent);
    QEvent languageChangeEvent(QEvent::LanguageChange);
    QCoreApplication::sendEvent(QCoreApplication::instance(), &languageChangeEvent);
}

void LanguageUtil::applyLanguageAsSystemDefault()
{
    const QString locale1Service = QStringLiteral("org.freedesktop.locale1");
    const QString locale1Path = QStringLiteral("/org/freedesktop/locale1");

    QDBusMessage message = QDBusMessage::createMethodCall( //
        locale1Service,
        locale1Path,
        QStringLiteral("org.freedesktop.locale1"),
        QStringLiteral("SetLocale") //
    );

    const QLocale locale = QLocale(m_currentLanguage);
    const QString lang = QStringLiteral("LANG=") + locale.name() + QStringLiteral(".UTF-8"); // e.g. "LANG=en_US.UTF-8"
    const bool interactive = false;
    message << QStringList{lang} << interactive;

    QDBusPendingReply<> reply = QDBusConnection::systemBus().asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
        watcher->deleteLater();

        if (watcher->isError()) {
            qCWarning(KDEInitialSystemSetupLanguage) << "Failed to set system default language:" << watcher->error().message();
        } else {
            qCInfo(KDEInitialSystemSetupLanguage) << "Successfully set system default language.";
        }
    });
}

void LanguageUtil::loadAvailableLanguages()
{
    m_availableLanguages = KLocalizedString::availableDomainTranslations("plasmashell").values();

    // Ensure we at least have English available
    if (!m_availableLanguages.contains(QStringLiteral("en_US"))) {
        m_availableLanguages.append(QStringLiteral("en_US"));
    }

    m_availableLanguages.sort();

    Q_EMIT availableLanguagesChanged();
}
