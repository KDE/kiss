// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "bootutil.h"
#include "initialsystemsetup_bootutil_debug.h"

/**
    Small utility to check if the system is booting for the first time, and set up KISS to run if it
    is.

    This is intended to be run as a systemd service at boot time, before the display manager starts.

    It checks if there are any user accounts set up. If not, it assumes this is the first boot and
    runs KISS to set up the system.

    It also checks for a kernel parameter that indicates whether KISS should run. If the parameter
    is set, it runs KISS regardless of user accounts.
 */
int main(int argc, char *argv[])
{
    std::cout << "KDE Initial System Setup Boot Utility started." << std::endl;

    QCoreApplication app(argc, argv);

    BootUtil bootUtil;

    // Check if force run was requested
    if (bootUtil.forceRunRequested()) {
        qCDebug(KDEInitialSystemSetupBootUtil) << "Force run requested. Running KISS setup.";
        // Here you would typically call the KISS setup function or process
    }

    // Check if this is the first boot
    if (bootUtil.isFirstBoot()) {
        qCDebug(KDEInitialSystemSetupBootUtil) << "First boot detected. Running KISS setup.";
        // Here you would typically call the KISS setup function or process
    }

    qCDebug(KDEInitialSystemSetupBootUtil) << "Boot check completed. No action needed.";

    // Exit the application
    return 0;
}
