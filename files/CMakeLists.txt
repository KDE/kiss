# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

install(
    FILES "kde-initial-system-setup.conf"
    DESTINATION  ${CMAKE_INSTALL_PREFIX}/lib/sysusers.d
)
    
install(
    FILES "kde-initial-system-setup.rules"
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/polkit-1/rules.d
)

configure_file(kde-initial-system-setup.service.in kde-initial-system-setup.service)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/kde-initial-system-setup.service
    DESTINATION ${KDE_INSTALL_SYSTEMDUNITDIR}/system
)
