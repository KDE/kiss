// SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <KPackage/Package>
#include <qqmlintegration.h>

#include "pagesmodel.h"

class QQmlEngine;
class QQuickItem;
class KLocalizedContext;


/**
 * Singleton class exposing global variables to the QML application.
 */
class InitialStart : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)

public:
    InitialStart(QObject *parent = nullptr);
    ~InitialStart() = default;

    QString username() const;
    void setUsername(const QString &username);

Q_SIGNALS:
    void usernameChanged();

private:
    QString m_username;
};
