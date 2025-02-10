# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: LGPL-2.0-or-later

add_subdirectory(prepare)
kpackage_install_package(prepare org.kde.plasma.initialstart.prepare packages plasma)

add_subdirectory(time)
kpackage_install_package(time org.kde.plasma.initialstart.time packages plasma)

kpackage_install_package(account org.kde.plasma.initialstart.account packages plasma)
kpackage_install_package(password org.kde.plasma.initialstart.password packages plasma)
kpackage_install_package(finished org.kde.plasma.initialstart.finished packages plasma)
