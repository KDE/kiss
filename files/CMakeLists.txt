# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

install(
    FILES "tmpfiles.conf"
    DESTINATION "lib/tmpfiles.d"
    RENAME "kde-initial-system-setup.conf"
)

install(
    FILES "sysuser.conf"
    DESTINATION  "lib/sysusers.d"
    RENAME "kde-initial-system-setup.conf"
)

install(
    FILES "polkit.rules"
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/polkit-1/rules.d
    RENAME "kde-initial-system-setup.rules"
)

# configure_file(systemd-first-run.service.in kde-initial-system-setup.service)
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/kde-initial-system-setup.service
#     DESTINATION ${KDE_INSTALL_SYSTEMDUNITDIR}/system
# )
