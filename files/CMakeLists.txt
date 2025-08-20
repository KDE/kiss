# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

configure_file(kde-initial-system-setup.service.in kde-initial-system-setup.service)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/kde-initial-system-setup.service
    DESTINATION ${KDE_INSTALL_SYSTEMDUNITDIR}/system
)

install(
    FILES "kde-initial-system-setup-polkit.rules"
    DESTINATION ${KDE_INSTALL_DATADIR}/polkit-1/rules.d
)

install(
    FILES "kde-initial-system-setup-sysuser.conf"
    DESTINATION  "lib/sysusers.d"
)

configure_file(kde-initial-system-setup-tmpfiles.conf.in kde-initial-system-setup-tmpfiles.conf)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/kde-initial-system-setup-tmpfiles.conf
    DESTINATION "lib/tmpfiles.d"
)

configure_file(kde-initial-system-setup.desktop.in kde-initial-system-setup.desktop)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/kde-initial-system-setup.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kde-initial-system-setup
)
