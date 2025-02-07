// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "initialstart.h"

InitialStart::InitialStart(QObject *parent)
    : QObject(parent)
{
}

void InitialStart::setUsername(const QString &username)
{
    if (m_username == username) {
        return;
    }
    m_username = username;
    Q_EMIT usernameChanged();
}

QString InitialStart::username() const
{
    return m_username;
}

#include "moc_initialstart.cpp"
