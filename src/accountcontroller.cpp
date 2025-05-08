// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "accountcontroller.h"

#include <QDBusObjectPath>

#include "accounts_interface.h"
#include "user.h"

using namespace Qt::StringLiterals;

AccountController::AccountController(QObject *parent)
    : QObject(parent)
    , m_dbusInterface(new OrgFreedesktopAccountsInterface(u"org.freedesktop.Accounts"_s, u"/org/freedesktop/Accounts"_s, QDBusConnection::systemBus(), this))
{
}

AccountController::~AccountController() = default;

QString AccountController::username() const
{
    return m_username;
}

void AccountController::setUsername(const QString &username)
{
    qWarning() << "Setting username to" << username;

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
    qWarning() << "Setting full name to" << fullName;

    if (m_fullName == fullName) {
        return;
    }

    m_fullName = fullName;
    Q_EMIT fullNameChanged();
}

bool AccountController::createUser()
{
    qWarning() << "Creating user" << m_username << "with full name" << m_fullName;

    bool isAdmin = false;
    QDBusPendingReply<QDBusObjectPath> reply = m_dbusInterface->CreateUser(m_username, m_fullName, static_cast<qint32>(isAdmin));
    reply.waitForFinished();
    if (reply.isValid()) {
        qWarning() << "User created with path" << reply.value().path();
        User *createdUser = new User(this);
        createdUser->setPath(reply.value());
        createdUser->setPassword(m_password);
        delete createdUser;
        return true;
    } else {
        qWarning() << "Failed to create user:" << reply.error().message();
        return false;
    }
}

QString AccountController::password() const
{
    return m_password;
}

void AccountController::setPassword(const QString &password)
{
    m_password = password;
    Q_EMIT passwordChanged();
}
