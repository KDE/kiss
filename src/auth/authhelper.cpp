// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>

#include <KLocalizedString>

#include "authhelper.h"

ActionReply KISSAuthHelper::writesddmconfig(const QVariantMap &args)
{
    ActionReply reply;
    bool autoLogin = args.value(QStringLiteral("autologin"), false).toBool();

    // Make sure the directory exists
    QFileInfo fileInfo(QStringLiteral("/etc/sddm.conf.d/kde-initial-system-setup.conf"));
    QDir dir = fileInfo.dir();

    // If autologin is to be disabled, remove the file if it exists
    if (!autoLogin) {
        if (fileInfo.exists()) {
            if (!QFile::remove(fileInfo.filePath())) {
                reply = ActionReply::HelperErrorReply();
                reply.setErrorDescription(i18n("Failed to remove file %1", fileInfo.filePath()));
                return reply;
            }
        }
        return ActionReply::SuccessReply();
    }

    // Ensure the directory exists
    if (!dir.exists()) {
        if (!dir.mkpath(QStringLiteral("."))) {
            reply = ActionReply::HelperErrorReply();
            reply.setErrorDescription(i18n("Failed to create directory %1", dir.absolutePath()));
            return reply;
        }
    }

    // Write the autologin configuration for SDDM
    QFile file(fileInfo.filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Failed to open file %1 for writing", fileInfo.filePath()));
        return reply;
    }

    QTextStream out(&file);
    out << "[Autologin]\n";
    out << "User=kde-initial-system-setup\n";
    // TODO: we may need to check which session is available first.
    // For example, openSUSE seems to use "plasmawayland.desktop", while Fedora uses "plasma.desktop".
    out << "Session=plasma\n";
    file.close();

    reply = ActionReply::SuccessReply();
    return reply;
}

KAUTH_HELPER_MAIN("org.kde.kiss", KISSAuthHelper)
