# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.0-or-later

add_subdirectory(account)
kpackage_install_package(account org.kde.initialsystemsetup.account packages plasma)

# add_subdirectory(cellular)
# kpackage_install_package(cellular org.kde.initialsystemsetup.cellular packages plasma)

add_subdirectory(finished)
kpackage_install_package(finished org.kde.initialsystemsetup.finished packages plasma)

add_subdirectory(keyboard)
kpackage_install_package(keyboard org.kde.initialsystemsetup.keyboard packages plasma)

add_subdirectory(language)
kpackage_install_package(language org.kde.initialsystemsetup.language packages plasma)

add_subdirectory(prepare)
kpackage_install_package(prepare org.kde.initialsystemsetup.prepare packages plasma)

add_subdirectory(screenbrightnessplugin)
kpackage_install_package(screenbrightnessplugin org.kde.initialsystemsetup.screenbrightnessplugin packages plasma)

add_subdirectory(time)
kpackage_install_package(time org.kde.initialsystemsetup.time packages plasma)

add_subdirectory(wifi)
kpackage_install_package(wifi org.kde.initialsystemsetup.wifi packages plasma)
