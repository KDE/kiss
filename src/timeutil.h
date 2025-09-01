// SPDX-FileCopyrightText: 2023 by Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <QProcess>
#include <qqmlregistration.h>

#include "timezonemodel.h"

class OrgFreedesktopTimedate1Interface;

class TimeUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool is24HourTime READ is24HourTime WRITE setIs24HourTime NOTIFY is24HourTimeChanged)
    Q_PROPERTY(QString currentTimeZone READ currentTimeZone WRITE setCurrentTimeZone NOTIFY currentTimeZoneChanged)
    Q_PROPERTY(TimeZoneFilterProxy *timeZones READ timeZones CONSTANT)

    /// This property holds the current user whose time information should be modified.
    /// \note In case it is empty, assume this is the current user.
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)

public:
    explicit TimeUtil(QObject *parent = nullptr);

    [[nodiscard]] bool is24HourTime() const;
    void setIs24HourTime(bool is24HourTime);

    [[nodiscard]] QString user() const;
    void setUser(const QString &user);

    QString currentTimeZone() const;
    void setCurrentTimeZone(const QString &timeZone);

    TimeZoneFilterProxy *timeZones() const;

Q_SIGNALS:
    void is24HourTimeChanged();
    void currentTimeZoneChanged();
    void userChanged();

private:
    bool m_is24HourTime;

    OrgFreedesktopTimedate1Interface *const m_dbusInterface;
    QString m_user;
    TimeZoneModel *const m_timeZoneModel;
    TimeZoneFilterProxy *const m_filterModel;
};
