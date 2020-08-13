// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#pragma once

#include <QObject>
#include <qqmlintegration.h>
class OrgFreedesktopAccountsInterface;

class AccountController: public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)

public:
    explicit AccountController(QObject *parent = nullptr);
    ~AccountController() override;

    QString username() const;
    void setUsername(const QString &username);

    QString fullName() const;
    void setFullName(const QString &fullName);

    Q_INVOKABLE bool createUser();

Q_SIGNALS:
    void usernameChanged();
    void fullNameChanged();

private:
    OrgFreedesktopAccountsInterface *const m_dbusInterface;

    QString m_username;
    QString m_fullName;
};
