# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: LGPL-2.0-or-later

add_subdirectory(prepare)
kpackage_install_package(prepare org.kde.initialsystemsetup.prepare packages plasma)

add_subdirectory(time)
kpackage_install_package(time org.kde.initialsystemsetup.time packages plasma)

kpackage_install_package(account org.kde.initialsystemsetup.account packages plasma)
kpackage_install_package(password org.kde.initialsystemsetup.password packages plasma)
kpackage_install_package(finished org.kde.initialsystemsetup.finished packages plasma)
kpackage_install_package(wifi org.kde.initialsystemsetup.wifi packages plasma)
kpackage_install_package(cellular org.kde.initialsystemsetup.cellular packages plasma)
