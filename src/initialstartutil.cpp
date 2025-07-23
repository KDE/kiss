// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <KAuth/Action>
#include <KAuth/ExecuteJob>

#include "initialstartutil.h"
#include "initialsystemsetup_debug.h"

InitialStartUtil::InitialStartUtil(QObject *parent)
    : QObject{parent}
{
    disableKISSAutologin();
}

QString InitialStartUtil::distroName() const
{
    return m_osrelease.name();
}

void InitialStartUtil::disableKISSAutologin()
{
    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.removeautologin"));
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    KAuth::ExecuteJob *job = action.execute();

    connect(job, &KJob::result, this, [job]() {
        if (job->error()) {
            qCWarning(KDEInitialSystemSetup) << "Failed to remove autologin configuration:" << job->errorString();
        } else {
            qCInfo(KDEInitialSystemSetup) << "Autologin configuration removed successfully.";
        }
    });

    job->start();
}
