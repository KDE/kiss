# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

add_executable(kde-initial-system-setup-auth-helper
    authhelper.cpp
    authhelper.h
)

target_link_libraries(kde-initial-system-setup-auth-helper
    Qt::Core
    KF6::AuthCore
    KF6::I18n
)

kauth_install_actions(org.kde.initialsystemsetup org.kde.initialsystemsetup.actions)
install(TARGETS kde-initial-system-setup-auth-helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
kauth_install_helper_files(kde-initial-system-setup-auth-helper org.kde.initialsystemsetup root)
