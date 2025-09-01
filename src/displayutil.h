// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QWindow>

/**
 * Utility class for managing display settings for new users.
 */
class DisplayUtil : public QObject
{
    Q_OBJECT

public:
    explicit DisplayUtil(QObject *parent = nullptr);

    void setGlobalThemeForNewUser(QWindow *window, QString userName);
    void setScalingForNewUser(QWindow *window, QString userName);

private:
    QString getGlobalTheme();
};
