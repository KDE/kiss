// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "bootutil.h"
#include "initialsystemsetup_bootutil_debug.h"

#include <iostream>

BootUtil::BootUtil(QObject *parent)
    : QObject(parent)
{
}

bool BootUtil::forceRunRequested() const
{
    // Check for the file /proc/cmdline for the parameter "kde.initial-setup=1"
    QFile file(QStringLiteral("/proc/cmdline"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Could not open /proc/cmdline" << std::endl;
        return false;
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    return content.contains(QStringLiteral("kde.initial-setup=1"));
}

bool BootUtil::isFirstBoot() const
{
    // Check for user accounts or other indicators of first boot
    return false;
}

void BootUtil::writeSDDMAutologin()
{
    // Make sure the directory exists
    QFileInfo fileInfo(QStringLiteral("/etc/sddm.conf.d/kde-initial-system-setup.conf"));
    QDir dir = fileInfo.dir();

    if (!dir.exists()) {
        if (!dir.mkpath(QStringLiteral("."))) {
            std::cerr << "Could not create directory: " << dir.path().toStdString() << std::endl;
            return;
        }
    }

    // Write the autologin configuration for SDDM
    QFile file(fileInfo.filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Could not open SDDM config file for writing." << std::endl;
        return;
    }

    QTextStream stream(&file);
    stream << "[Autologin]\n";
    stream << "User=kde-initial-system-setup\n";
    // TODO: we may need to check which session is available first.
    // For example, openSUSE seems to use "plasmawayland.desktop".
    stream << "Session=plasma.desktop\n";

    file.close();
}
