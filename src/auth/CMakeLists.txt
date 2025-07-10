# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

ecm_qt_declare_logging_category(logging_SRCS
    HEADER "initialsystemsetup_auth_debug.h"
    IDENTIFIER "KDEInitialSystemSetupAuthHelper"
    CATEGORY_NAME "org.kde.initialsystemsetup.authhelper"
    DESCRIPTION "KDE Initial System Setup Authentication Helper"
    DEFAULT_SEVERITY Debug
    EXPORT INITIALSYSTEMSETUP_AUTHHELPER
)

add_executable(kde-initial-system-setup-auth-helper
    authhelper.cpp
    authhelper.h
    ${logging_SRCS}
)

target_link_libraries(kde-initial-system-setup-auth-helper
    Qt::Core
    KF6::AuthCore
    KF6::I18n
)

kauth_install_actions(org.kde.kiss org.kde.kiss.actions)
install(TARGETS kde-initial-system-setup-auth-helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
kauth_install_helper_files(kde-initial-system-setup-auth-helper org.kde.kiss root)
