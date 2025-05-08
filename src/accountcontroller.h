// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#pragma once

#include <QDBusObjectPath>
#include <QObject>
#include <qqmlintegration.h>

class OrgFreedesktopAccountsInterface;

class AccountController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    explicit AccountController(QObject *parent = nullptr);
    ~AccountController() override;

    QString username() const;
    void setUsername(const QString &username);

    QString fullName() const;
    void setFullName(const QString &fullName);

    QString password() const;
    void setPassword(const QString &password);

    Q_INVOKABLE bool createUser();

Q_SIGNALS:
    void usernameChanged();
    void fullNameChanged();
    void passwordChanged();

private:
    OrgFreedesktopAccountsInterface *const m_dbusInterface;

    QString m_username;
    QString m_fullName;
    QString m_password;
};
