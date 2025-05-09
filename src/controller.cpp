// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
}

void Controller::setUsername(const QString &username)
{
    if (m_username == username) {
        return;
    }
    m_username = username;
    Q_EMIT usernameChanged();
}

QString Controller::username() const
{
    return m_username;
}

#include "moc_controller.cpp"
