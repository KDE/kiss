# SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

add_subdirectory(plugins)
add_subdirectory(plugins/users)
add_subdirectory(plugins/license)
add_subdirectory(plugins/sample)

set(SOURCES
    main.cpp
    settings.cpp
    kiss.cpp
    pages/localepage.cpp
    pages/readypage.cpp
    resources.qrc
)

add_executable(org.kde.initialsystemsetup ${SOURCES})

target_compile_definitions(org.kde.initialsystemsetup
		PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_link_libraries(org.kde.initialsystemsetup
	PRIVATE
		Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2 Qt5::DBus
		KF5::I18n KF5::ConfigCore KF5::ConfigGui KF5::CoreAddons
		PkgConfig::Croutons
		crack
        kissplugins
)

kconfig_add_kcfg_files(org.kde.initialsystemsetup initialsystemsetup.kcfgc)

configure_file(org.kde.initialsystemsetup.service.in org.kde.initialsystemsetup.service @ONLY)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/org.kde.initialsystemsetup.service
	DESTINATION ${KDE_INSTALL_SYSTEMDUNITDIR}/system
)

install(TARGETS org.kde.initialsystemsetup
	PERMISSIONS ${DefaultPermissions} SETUID
	DESTINATION ${KDE_INSTALL_BINDIR}
)
