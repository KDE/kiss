// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.0-or-later

#pragma once

#include <QDBusObjectPath>
#include <QObject>
#include <QQmlEngine>
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
    ~AccountController() override;

    /*
     * Returns the singleton instance of AccountController.
     *
     * This is intended to be used automatically by the QML engine.
     */
    static AccountController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    /*
     * Returns the singleton instance of AccountController.
     *
     * If it doesn't exist, it will create one.
     */
    static AccountController *instance();

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
    /*
     * Private constructor to enforce singleton pattern.
     *
     * Use `instance()` to get the singleton instance.
     */
    explicit AccountController(QObject *parent = nullptr);

    /*
     * Static instance of AccountController.
     */
    static AccountController *s_instance;

    OrgFreedesktopAccountsInterface *const m_dbusInterface;

    QString m_username;
    QString m_fullName;
    QString m_password;
};
