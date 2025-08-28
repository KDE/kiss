// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>
#include <QProcess>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusPendingReply>

#include <KAuth/HelperSupport>
#include <KLocalizedString>

#include "authhelper.h"
#include "config-kiss.h"

const QString SDDM_AUTOLOGIN_CONFIG_PATH = QStringLiteral("/etc/sddm.conf.d/99-kde-initial-system-setup.conf");

ActionReply KISSAuthHelper::createnewuserautostarthook(const QVariantMap &args)
{
    ActionReply reply;

    if (!args.contains(QStringLiteral("username")) || !args[QStringLiteral("username")].canConvert<QString>()) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Username argument is missing or invalid."));
        return reply;
    }

    QString username = args[QStringLiteral("username")].toString();
    QString autostartDirPath = QDir::cleanPath(QStringLiteral("/home/") + username + QStringLiteral("/.config/autostart"));
    QDir autostartDir(autostartDirPath);

    // Ensure the autostart directory exists
    if (!autostartDir.exists() && !autostartDir.mkpath(QStringLiteral("."))) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18nc("%1 is a directory path", "Failed to create autostart directory: %1", autostartDirPath));
        return reply;
    }

    // Create the desktop entry file
    QString desktopFilePath = autostartDir.filePath(QStringLiteral("remove-autologin.desktop"));
    QFile desktopFile(desktopFilePath);
    if (!desktopFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18nc("%1 is a file path", "Failed to open file for writing: %1", desktopFilePath));
        return reply;
    }

    QString initialSetupExecutablePath = QStringLiteral(KDE_INITIAL_SETUP_LIBEXECDIR) + QStringLiteral("/kde-initial-system-setup");
    if (initialSetupExecutablePath.isEmpty()) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Failed to find the initial setup executable path."));
        return reply;
    }

    QTextStream stream(&desktopFile);
    stream << "[Desktop Entry]\n";
    stream << "Type=Application\n";
    stream << "Name=Remove KISS Autologin\n";
    stream << "Exec=sh -c \"" << initialSetupExecutablePath << " --remove-autologin && rm --force '" << desktopFilePath << "'\"\n";
    stream << "X-KDE-StartupNotify=false\n";
    stream << "NoDisplay=true\n";
    desktopFile.close();

    reply = ActionReply::SuccessReply();
    reply.setData({{QStringLiteral("autostartFilePath"), desktopFilePath}});
    return reply;
}

ActionReply KISSAuthHelper::disablesystemdunit(const QVariantMap &args)
{
    Q_UNUSED(args);

    ActionReply actionReply;

    QDBusInterface systemdInterface(QStringLiteral("org.freedesktop.systemd1"),
                                    QStringLiteral("/org/freedesktop/systemd1"),
                                    QStringLiteral("org.freedesktop.systemd1.Manager"),
                                    QDBusConnection::systemBus());

    QStringList unitFiles = {QStringLiteral("kde-initial-system-setup.service")};
    bool runtime = false; // Disable permanently, not just for runtime

    QDBusPendingReply<> dbusReply = systemdInterface.call(QStringLiteral("DisableUnitFiles"), unitFiles, runtime);
    dbusReply.waitForFinished();

    if (dbusReply.isError()) {
        actionReply = ActionReply::HelperErrorReply();
        actionReply.setErrorDescription(i18nc("%1 is an error message", "Failed to disable systemd unit: %1", dbusReply.error().message()));
        return actionReply;
    }

    return ActionReply::SuccessReply();
}

ActionReply KISSAuthHelper::removeautologin(const QVariantMap &args)
{
    Q_UNUSED(args);

    ActionReply reply;
    QFileInfo fileInfo(SDDM_AUTOLOGIN_CONFIG_PATH);

    if (!fileInfo.exists()) {
        return ActionReply::SuccessReply();
    }

    if (!QFile::remove(fileInfo.filePath())) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18nc("%1 is a file path", "Failed to remove file %1", fileInfo.filePath()));
        return reply;
    }

    return ActionReply::SuccessReply();
}

ActionReply KISSAuthHelper::setnewuserhomedirectoryownership(const QVariantMap &args)
{
    ActionReply reply;

    if (!args.contains(QStringLiteral("username")) || !args[QStringLiteral("username")].canConvert<QString>()) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Username argument is missing or invalid."));
        return reply;
    }

    QString username = args[QStringLiteral("username")].toString();
    QString homePath = QDir::cleanPath(QStringLiteral("/home/") + username);

    // Recursively set ownership of the home directory to the new user
    int exitCode = QProcess::execute(QStringLiteral("chown"), {QStringLiteral("-R"), username + QStringLiteral(":") + username, homePath});

    if (exitCode != 0) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18nc("%1 is a directory path, %2 an exit code", "Failed to set ownership for home directory %1: exit code %2", homePath, exitCode));
        return reply;
    }

    return ActionReply::SuccessReply();
}

ActionReply KISSAuthHelper::setnewusertempautologin(const QVariantMap &args)
{
    ActionReply reply;

    if (!args.contains(QStringLiteral("username")) || !args[QStringLiteral("username")].canConvert<QString>()) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18n("Username argument is missing or invalid."));
        return reply;
    }

    QString username = args[QStringLiteral("username")].toString();

    QFile file(SDDM_AUTOLOGIN_CONFIG_PATH);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(i18nc("%1 is a file path", "Failed to open file %1 for writing.", SDDM_AUTOLOGIN_CONFIG_PATH));
        return reply;
    }

    QTextStream stream(&file);
    stream << "[Autologin]\n";
    stream << "User=" << username << "\n";
    stream << "Session=plasma\n";
    stream << "Relogin=true\n"; // Set Relogin to true for temporary autologin
    file.close();

    return ActionReply::SuccessReply();
}

KAUTH_HELPER_MAIN("org.kde.initialsystemsetup", KISSAuthHelper)
