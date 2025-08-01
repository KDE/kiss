# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: BSD-2-Clause

add_subdirectory(bootutil)
add_subdirectory(components)
add_subdirectory(packagestructure)

set_source_files_properties(org.freedesktop.Accounts.xml PROPERTIES NO_NAMESPACE TRUE)
set_source_files_properties(org.freedesktop.Accounts.User.xml PROPERTIES NO_NAMESPACE TRUE)

ecm_qt_declare_logging_category(logging_SRCS
    HEADER "initialsystemsetup_debug.h"
    IDENTIFIER "KDEInitialSystemSetup"
    CATEGORY_NAME "org.kde.initialsystemsetup"
    DESCRIPTION "KDE Initial System Setup"
    EXPORT INITIALSYSTEMSETUP
)

qt_add_dbus_interface(initialstart_DBUS_SRCS
    org.freedesktop.Accounts.xml
    accounts_interface
)

qt_add_dbus_interface(initialstart_DBUS_SRCS
    org.freedesktop.Accounts.User.xml
    user_interface
)

add_executable(kde-initial-system-setup
    main.cpp
    pagesmodel.cpp
    pagesmodel.h
    controller.cpp
    controller.h
    accountcontroller.cpp
    accountcontroller.h
    user.cpp
    user.h
    initialstartutil.cpp
    initialstartutil.h
    keyboardutil.cpp
    keyboardutil.h
    ${initialstart_DBUS_SRCS}
    ${logging_SRCS}
)

# FreeBSD systems might have libxcrypt but their shadow equivalent doesn't use it
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    pkg_check_modules(libxcrypt libxcrypt>=4)
    if(libxcrypt_FOUND)
        target_compile_definitions(kde-initial-system-setup PRIVATE -DHAVE_CRYPT_GENSALT=true)
    else()
        target_compile_definitions(kde-initial-system-setup PRIVATE -DHAVE_CRYPT_GENSALT=false)
    endif()
else()
    target_compile_definitions(kde-initial-system-setup PRIVATE -DHAVE_CRYPT_GENSALT=false)
endif()

ecm_add_qml_module(kde-initial-system-setup GENERATE_PLUGIN_SOURCE
    URI "org.kde.initialsystemsetup"
    DEPENDENCIES
        QtGui
        QtQuick
)

qt_target_qml_sources(kde-initial-system-setup
    QML_FILES
        qml/Main.qml
        qml/Wizard.qml
        qml/LandingComponent.qml
)

target_link_libraries(kde-initial-system-setup
    PUBLIC
        Qt::Widgets
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::QuickControls2
        Qt::DBus
        Qt::Svg
        KF6::I18n
        KF6::I18nQml
        KF6::Package
        KF6::ConfigGui
        crypt
        componentsplugin
        componentspluginplugin
)

install(TARGETS kde-initial-system-setup RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})
