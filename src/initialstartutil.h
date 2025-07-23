// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <KOSRelease>
#include <QObject>
#include <qqmlintegration.h>

class InitialStartUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString distroName READ distroName CONSTANT);

public:
    InitialStartUtil(QObject *parent = nullptr);

    QString distroName() const;

private:
    KOSRelease m_osrelease;

    /**
     * Removes the autologin configuration for KISS.
     *
     * This allows the next login to be a normal login, unless the KISS systemd service runs again.
     */
    void disableKISSAutologin();
};
