// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "displayutil.h"
#include "initialstartutil.h"
#include "initialsystemsetup_debug.h"

#include <KAuth/Action>
#include <KAuth/ExecuteJob>

#include <QApplication>

InitialStartUtil::InitialStartUtil(QObject *parent)
    : QObject{parent}
    , m_accountController(AccountController::instance())
{
    QList<QWindow *> topLevelWindows = QGuiApplication::topLevelWindows();
    m_window = topLevelWindows.isEmpty() ? nullptr : topLevelWindows.first();
    disableKISSAutologin();
}

QString InitialStartUtil::distroName() const
{
    return m_osrelease.name();
}

void InitialStartUtil::finish()
{
    disableSystemdUnit();

    const bool userCreated = m_accountController->createUser();
    if (!userCreated) {
        qCWarning(KDEInitialSystemSetup) << "Failed to create user:" << m_accountController->username();
        // TODO: Handle the error appropriately, e.g., show a message to the user
        return;
    }

    // Temporarily disabling the automatic session transition because using SDDM's
    // Autologin causes some issues, like being unable to create a wallet and potentially
    // connecting to new wifi networks until after a reboot. This isn't an issue when the user
    // logs in normally with their password. Re-enable these when we can ensure the automatic
    // transition doesn't cause such issues.
    // setNewUserTempAutologin();
    // createNewUserAutostartHook();

    // TODO: Set new user preferences re: dark mode, keyboard layout, etc.
    DisplayUtil displayUtil;
    displayUtil.setGlobalThemeForNewUser(m_window, m_accountController->username());

    setNewUserHomeDirectoryOwnership();
    logOut();
}

void InitialStartUtil::disableKISSAutologin()
{
    qCInfo(KDEInitialSystemSetup) << "Removing autologin configuration for KISS user.";

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.removeautologin"));
    action.setParentWindow(m_window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to remove autologin configuration:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Autologin configuration removed successfully.";
    }
}

void InitialStartUtil::disableSystemdUnit()
{
    qCInfo(KDEInitialSystemSetup) << "Disabling systemd unit for initial system setup.";

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.disablesystemdunit"));
    action.setParentWindow(m_window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to disable systemd unit:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Systemd unit disabled successfully.";
    }
}

void InitialStartUtil::logOut()
{
    m_session.requestLogout(SessionManagement::ConfirmationMode::Skip);
}

void InitialStartUtil::setNewUserHomeDirectoryOwnership()
{
    const QString username = m_accountController->username();
    qCInfo(KDEInitialSystemSetup) << "Setting ownership of new user's home directory to:" << username;

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.setnewuserhomedirectoryownership"));
    action.setParentWindow(m_window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.setArguments({{QStringLiteral("username"), username}});
    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set new user home directory ownership:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "New user home directory ownership set successfully.";
    }
}

void InitialStartUtil::setNewUserTempAutologin()
{
    const QString username = m_accountController->username();
    qCInfo(KDEInitialSystemSetup) << "Setting temporary autologin for new user:" << username;

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.setnewusertempautologin"));
    action.setParentWindow(m_window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.setArguments({{QStringLiteral("username"), username}});
    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to set temporary autologin for new user:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Temporary autologin set for new user successfully.";
    }
}

void InitialStartUtil::createNewUserAutostartHook()
{
    const QString username = m_accountController->username();
    qCInfo(KDEInitialSystemSetup) << "Creating autostart hook for new user:" << username;

    KAuth::Action action(QStringLiteral("org.kde.initialsystemsetup.createnewuserautostarthook"));
    action.setParentWindow(m_window);
    action.setHelperId(QStringLiteral("org.kde.initialsystemsetup"));
    action.setArguments({{QStringLiteral("username"), username}});
    KAuth::ExecuteJob *job = action.execute();

    if (!job->exec()) {
        qCWarning(KDEInitialSystemSetup) << "Failed to create autostart hook for new user:" << job->errorString();
    } else {
        qCInfo(KDEInitialSystemSetup) << "Autostart hook created successfully for new user.";
    }
}

#include "initialstartutil.moc"
