// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

#include "bootutil.h"
#include "initialsystemsetup_bootutil_debug.h"

/**
    Small utility to determine if the KDE Initial System Setup (KISS) should run at boot time, and to run it if necessary.

    This is intended to be run as a systemd service at boot time, before the display manager starts.

    This utility expects to be called one of the following ways:

    1. With the command line flag `--first-run`, which indicates that this is the first boot and
       KISS should run.
    2. With no command line arguments, which indicates that this is a regular boot and KISS should not run unless the
       `kde.initial-setup=1` kernel parameter is set.

    These should be managed by the systemd service files.
 */
int main(int argc, char *argv[])
{
    qCInfo(KDEInitialSystemSetupBootUtil) << "KDE Initial System Setup Boot Utility started.";

    QCoreApplication app(argc, argv);

    BootUtil bootUtil;

    const bool isFirstRun = app.arguments().contains(QStringLiteral("--first-run"));

    if (isFirstRun) {
        qCInfo(KDEInitialSystemSetupBootUtil) << "First boot detected. Running setup...";
        bootUtil.writeSDDMAutologin(true);
        return 0;
    }

    if (bootUtil.forceRunRequested()) {
        qCInfo(KDEInitialSystemSetupBootUtil) << "Force run requested. Running setup...";
        bootUtil.writeSDDMAutologin(true);
        return 0;
    }

    qCInfo(KDEInitialSystemSetupBootUtil) << "Boot check completed. No action needed.";

    // Exit the application
    return 0;
}
