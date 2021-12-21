# SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.5)

project(KDEInitialSystemSetup LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ECM CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)

find_package(Qt5 COMPONENTS Core Widgets Quick QuickControls2 DBus REQUIRED)
find_package(KF5I18n)
find_package(KF5Config)
find_package(KF5CoreAddons)
find_package(PkgConfig REQUIRED)

pkg_check_modules(Croutons REQUIRED IMPORTED_TARGET croutons)

set(DefaultPermissions
	OWNER_WRITE OWNER_READ OWNER_EXECUTE
	GROUP_READ GROUP_EXECUTE
	WORLD_READ WORLD_EXECUTE
)

add_subdirectory(src)
