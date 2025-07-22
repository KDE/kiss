// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>

#include "bootutil.h"
#include "initialsystemsetup_bootutil_debug.h"

BootUtil::BootUtil(QObject *parent)
    : QObject(parent)
{
}

bool BootUtil::forceRunRequested() const
{
    // Check for the file /proc/cmdline for the parameter "kde.initial-setup=1"
    QFile file(QStringLiteral("/proc/cmdline"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCWarning(KDEInitialSystemSetupBootUtil) << "Could not open /proc/cmdline";
        return false;
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    return content.contains(QStringLiteral("kde.initial-setup=1"));
}

bool BootUtil::writeSDDMAutologin(const bool autoLogin)
{
    // Make sure the directory exists
    const QString configFilePath = QStringLiteral("/etc/sddm.conf.d/99-kde-initial-system-setup.conf");
    QFileInfo fileInfo(configFilePath);
    QDir dir = fileInfo.dir();

    // If autologin is to be disabled, remove the file if it exists
    if (!autoLogin) {
        if (fileInfo.exists()) {
            if (!QFile::remove(fileInfo.filePath())) {
                qCWarning(KDEInitialSystemSetupBootUtil) << "Failed to remove file:" << fileInfo.filePath();
                return false;
            }
        }
        return true;
    }

    if (!dir.exists() && !dir.mkpath(QStringLiteral("."))) {
        qCWarning(KDEInitialSystemSetupBootUtil) << "Failed to create directory:" << dir.absolutePath();
        return false;
    }

    QFile file(configFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCWarning(KDEInitialSystemSetupBootUtil) << "Failed to open file for writing:" << file.fileName();
        return false;
    }

    // Write the autologin configuration for SDDM
    QTextStream stream(&file);
    stream << "[Autologin]\n";
    stream << "User=kde-initial-system-setup\n";
    stream << "Session=plasma\n";
    file.close();

    qCInfo(KDEInitialSystemSetupBootUtil) << "SDDM autologin configuration written successfully.";
    return true;
}

#include "bootutil.moc"
