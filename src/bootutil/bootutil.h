// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>

class BootUtil : public QObject
{
    Q_OBJECT

public:
    explicit BootUtil(QObject *parent = nullptr);

    /**
     * @brief Checks if force run was requested with a kernel parameter.
     *
     * This checks for the presence of a specific kernel parameter that indicates
     * whether KISS should run regardless of user accounts being present.
     *
     * The expected parameter is "kde.initial-setup=1".
     *
     * @return true if force run is requested, false otherwise.
     */
    bool forceRunRequested() const;

    /**
     * Writes the autologin configuration for SDDM.
     *
     * This function writes the necessary configuration to enable autologin
     * for the SDDM display manager for the user "kde-initial-system-setup".
     *
     * @param autoLogin If true, enables autologin; if false, disables it.
     * @return true if the operation was successful, false otherwise.
     */
    bool writeSDDMAutologin(const bool autoLogin);
};
