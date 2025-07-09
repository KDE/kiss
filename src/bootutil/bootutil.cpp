// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QFile>
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
