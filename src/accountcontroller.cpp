// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "accountcontroller.h"

#include <QDebug>
#include <QDBusObjectPath>

#include "accounts_interface.h"
#include "user.h"

using namespace Qt::StringLiterals;

AccountController::AccountController(QObject *parent)
    : QObject(parent)
    , m_dbusInterface(new OrgFreedesktopAccountsInterface(u"org.freedesktop.Accounts"_s,
                                                          u"/org/freedesktop/Accounts"_s,
                                                          QDBusConnection::systemBus(),
                                                          this))
{
}

AccountController::~AccountController() = default;

QString AccountController::username() const
{
    return m_username;
}

void AccountController::setUsername(const QString &username)
{
    if (m_username == username) {
        return;
    }
    m_username = username;
    Q_EMIT usernameChanged();
}

QString AccountController::fullName() const
{
    return m_fullName;
}

void AccountController::setFullName(const QString &fullName)
{
    if (m_fullName == fullName) {
        return;
    }

    m_fullName = fullName;
    Q_EMIT fullNameChanged();
}

bool AccountController::createUser()
{
    bool isAdmin = false;
    QDBusPendingReply<QDBusObjectPath> reply = m_dbusInterface->CreateUser(m_username, m_fullName, static_cast<qint32>(isAdmin));
    reply.waitForFinished();
    if (reply.isValid()) {
        m_dbusPath = reply.value();
        return true;
    }
    return false;
}

QString AccountController::password() const
{
    return m_password;
}

void AccountController::setPassword(const QString &password)
{
    if (m_password == password && !m_dbusPath.path().isEmpty()) {
        return;
    }

    m_password = password;
    Q_EMIT passwordChanged();

    User createdUser;
    createdUser.setPath(m_dbusPath);
    createdUser.setPassword(m_password);
}
