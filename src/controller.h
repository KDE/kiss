// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <qqmlintegration.h>

class QQmlEngine;
class QQuickItem;
class KLocalizedContext;

/**
 * Singleton class exposing global variables to the QML application.
 */
class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)

public:
    Controller(QObject *parent = nullptr);
    ~Controller() = default;

    QString username() const;
    void setUsername(const QString &username);

Q_SIGNALS:
    void usernameChanged();

private:
    QString m_username;
};
