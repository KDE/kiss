// SPDX-FileCopyrightText: 2023 by Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "timeutil.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTimeZone>

#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::StringLiterals;

static const QString format24hours = u"HH:mm:ss"_s;
static const QString format12hours = u"HH:mm:ss ap"_s;


TimeUtil::TimeUtil(QObject *parent)
    : QObject{parent}
    , m_timeZoneModel{new TimeZoneModel{this}}
    , m_filterModel{new TimeZoneFilterProxy{this}}
{
    m_filterModel->setSourceModel(m_timeZoneModel);

    // retrieve is24HourTime
    auto config = KSharedConfig::openConfig(u"kdeglobals"_s, KConfig::SimpleConfig);
    auto group = KConfigGroup(config, "Locale"_L1);
    m_is24HourTime = group.readEntry(u"TimeFormat"_s, format24hours) == format24hours;
}

bool TimeUtil::is24HourTime() const
{
    return m_is24HourTime;
}

void TimeUtil::setIs24HourTime(bool is24HourTime)
{
    if (is24HourTime != m_is24HourTime) {
        auto config = KSharedConfig::openConfig("kdeglobals"_L1, KConfig::SimpleConfig);
        auto group = KConfigGroup(config, "Locale"_L1);
        group.writeEntry(u"TimeFormat"_s, is24HourTime ? format24hours : format12hours, KConfig::Notify);
        config->sync();

        m_is24HourTime = is24HourTime;
        Q_EMIT is24HourTimeChanged();
    }
}

QString TimeUtil::currentTimeZone() const
{
    return QString::fromUtf8(QTimeZone::systemTimeZoneId());
}

void TimeUtil::setCurrentTimeZone(const QString &timeZone)
{
    QProcess::execute(u"timedatectl"_s, {u"set-timezone"_s, timeZone});
    Q_EMIT currentTimeZoneChanged();
}

TimeZoneFilterProxy *TimeUtil::timeZones() const
{
    return m_filterModel;
}
