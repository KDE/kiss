// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <KAuth/ActionReply>
#include <KAuth/HelperSupport>

using namespace KAuth;

class KISSAuthHelper : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    ActionReply writesddmconfig(const QVariantMap &args);
};
