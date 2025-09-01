// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "displayutil.h"
#include "initialsystemsetup_debug.h"

#include <KAuth/Action>
#include <KAuth/ExecuteJob>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QWindow>

DisplayUtil::DisplayUtil(QObject *parent)
    : QObject(parent)
{
}

void DisplayUtil::setGlobalThemeForNewUser(QWindow *window, QString userName)
{
    qCInfo(KDEInitialSystemSetup) << "Setting global theme for new user.";

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.setnewuserglobaltheme"));
    action.setParentWindow(window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.addArgument(QStringLiteral("username"), userName);

    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set global theme for new user:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Global theme for new user set successfully.";
    }
}

void DisplayUtil::setScalingForNewUser(QWindow *window, QString userName)
{
    qCInfo(KDEInitialSystemSetup) << "Setting scaling for new user:" << userName;

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.setnewuserdisplayscaling"));
    action.setParentWindow(window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.addArgument(QStringLiteral("username"), userName);

    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set scaling for new user.";
    } else {
        qCInfo(KDEInitialSystemSetup) << "Set scaling for new user.";
    }
}
