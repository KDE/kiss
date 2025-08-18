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
     * Writes the autologin configuration for SDDM.
     *
     * This function writes the necessary configuration to enable autologin
     * for the SDDM display manager for the user "kde-initial-system-setup".
     *
     * @param autoLogin If true, enables autologin; if false, disables it.
     * @return true if the operation was successful, false otherwise.
     */
    bool writeSDDMAutologin(const bool autoLogin);

private:
    /**
     * Removes the default autologin entry some distros have in the kde_settings.conf
     *
     * Some distros have this autologin entry populated but with empty values, which prevents our config
     * from being applied correctly.
     */
    void removeEmptyAutologinEntry();
};
