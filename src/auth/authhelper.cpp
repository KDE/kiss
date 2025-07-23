// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>

#include <KAuth/HelperSupport>
#include <KLocalizedString>

#include "authhelper.h"

const QString SDDM_AUTOLOGIN_CONFIG_PATH = QStringLiteral("/etc/sddm.conf.d/99-kde-initial-system-setup.conf");

ActionReply KISSAuthHelper::removeautologin(const QVariantMap &args)
{
    Q_UNUSED(args);

    ActionReply reply;
    QFileInfo fileInfo(SDDM_AUTOLOGIN_CONFIG_PATH);

    if (!fileInfo.exists()) {
        return ActionReply::SuccessReply();
    }

    // Attempt to remove the file
    if (!QFile::remove(fileInfo.filePath())) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Failed to remove file %1", fileInfo.filePath()));
        return reply;
    }

    return ActionReply::SuccessReply();
}

KAUTH_HELPER_MAIN("org.kde.initialsystemsetup", KISSAuthHelper)
