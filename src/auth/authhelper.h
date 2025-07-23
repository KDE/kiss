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
     * Removes the configuration file that enables autologin for KISS.
     *
     * @param args The arguments passed to the action (not used here).
     * @return An ActionReply indicating success or failure.
     */
    ActionReply removeautologin(const QVariantMap &args);
};
