set(SOURCES
    main.cpp
    settings.cpp
    kiss.cpp
    resources.qrc
)

qt5_add_dbus_interface(SOURCES
    dbus/org.freedesktop.Accounts.Service.xml
    AccountsService
)
qt5_add_dbus_interface(SOURCES
    dbus/org.freedesktop.Accounts.User.xml
    User
)

add_executable(org.kde.initialsystemsetup ${SOURCES})

target_compile_definitions(org.kde.initialsystemsetup
		PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_link_libraries(org.kde.initialsystemsetup
	PRIVATE
		Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2 Qt5::DBus
		KF5::I18n KF5::ConfigCore
		PkgConfig::GIO
		crack
)

configure_file(org.kde.initialsystemsetup.service.in org.kde.initialsystemsetup.service @ONLY)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/org.kde.initialsystemsetup.service
	DESTINATION ${KDE_INSTALL_SYSTEMDUNITDIR}/system
)

install(
	FILES org.kde.initialsystemsetup.gschema.xml
	DESTINATION ${KDE_INSTALL_DATADIR}/glib-2.0/schemas
)

install(CODE "execute_process(COMMAND glib-compile-schemas ${KDE_INSTALL_FULL_DATADIR}/glib-2.0/schemas)")

install(TARGETS org.kde.initialsystemsetup
	PERMISSIONS ${DefaultPermissions} SETUID
	DESTINATION ${KDE_INSTALL_BINDIR}
)
