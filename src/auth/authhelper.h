// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <KAuth/ActionReply>

using namespace KAuth;

class KISSAuthHelper : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    /**
     * Creates an autostart hook for the newly created user to remove the autologin configuration.
     *
     * This function creates a desktop entry in the new user's autostart directory that will
     * execute a script to remove the autologin configuration when the session transitions to the new user.
     *
     * @param args The arguments passed to the action, which should include:
     * - String: "username": The username of the newly created user.
     * @return An ActionReply indicating success or failure.
     */
    ActionReply createnewuserautostarthook(const QVariantMap &args);

    /**
     * Disables the systemd unit for the initial system setup.
     *
     * This action is used to disable the systemd unit which runs the initial system setup
     * once the first user has been created.
     *
     * @param args The arguments passed to the action (not used here).
     * @return An ActionReply indicating success or failure.
     */
    ActionReply disablesystemdunit(const QVariantMap &args);

    /**
     * Removes the configuration file that enables autologin for KISS.
     *
     * @param args The arguments passed to the action (not used here).
     * @return An ActionReply indicating success or failure.
     */
    ActionReply removeautologin(const QVariantMap &args);

    /**
     * Sets the global theme for the newly created user.
     *
     * @param args The arguments passed to the action, which should include:
     * - String: "username": The username of the newly created user.
     * @return An ActionReply indicating success or failure.
     */
    ActionReply setnewuserglobaltheme(const QVariantMap &args);

    /**
     * Sets the ownership of the new user's home directory to the newly created user.
     *
     * This is necessary to ensure that the new user has proper ownership of their home directory
     * after KISS has added files like the autostart hook, otherwise when the new user logs in,
     * they may not have the correct permissions to access their own files.
     *
     * @param args The arguments passed to the action, which should include:
     * - String: "username": The username of the newly created user.
     * @return An ActionReply indicating success or failure.
     */
    ActionReply setnewuserhomedirectoryownership(const QVariantMap &args);

    /**
     * Sets the configuration for the newly created user to login automatically.
     *
     * This sets an autologin config with `Relogin=true`, so we can switch from the
     * KISS user to the new user when setup is complete.
     *
     * @param args The arguments passed to the action, which should include:
     * - String: "username": The username of the newly created user.
     * @return An ActionReply indicating success or failure.
     */
    ActionReply setnewusertempautologin(const QVariantMap &args);
};
