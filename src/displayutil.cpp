// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "displayutil.h"
#include "initialsystemsetup_debug.h"

#include <KAuth/Action>
#include <KAuth/ExecuteJob>
#include <KConfigGroup>
#include <KSharedConfig>

DisplayUtil::DisplayUtil(QObject *parent)
    : QObject(parent)
{
}

QString DisplayUtil::getColorScheme()
{
    KSharedConfigPtr config = KSharedConfig::openConfig(QStringLiteral("/run/kde-initial-system-setup/.config/kdeglobals"));
    KConfigGroup generalGroup = config->group(QStringLiteral("General"));
    QString colorScheme = generalGroup.readEntry(QStringLiteral("ColorScheme"), QStringLiteral(""));
    return colorScheme;
}

void DisplayUtil::setColorSchemeForNewUser(QWindow *window, QString userName)
{
    const QString colorScheme = getColorScheme();
    qCInfo(KDEInitialSystemSetup) << "Setting color scheme for new user:" << userName << "to" << colorScheme;

    if (colorScheme.isEmpty()) {
        qCWarning(KDEInitialSystemSetup) << "No color scheme found to set for new user.";
        return;
    }

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.setnewusercolorscheme"));
    action.setParentWindow(window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.addArgument(QStringLiteral("username"), userName);
    action.addArgument(QStringLiteral("colorscheme"), colorScheme);

    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set color scheme for new user.";
    } else {
        qCInfo(KDEInitialSystemSetup) << "Color scheme for new user:" << userName << "set to" << colorScheme;
    }
}
