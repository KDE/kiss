# SPDX-FileCopyrightText: 2024 Devin Lin <devin@kde.org>
# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(screenbrightnessplugin
    URI org.kde.initialsystemsetup.screenbrightnessplugin
    GENERATE_PLUGIN_SOURCE
)

qt_add_dbus_interfaces(DBUS_SRCS dbus/org.kde.Solid.PowerManagement.Actions.BrightnessControl.xml)

ecm_qt_declare_logging_category(logging_SRCS
    HEADER screenbrightnessplugin_debug.h
    IDENTIFIER "ScreenBrightnessPlugin"
    CATEGORY_NAME "org.kde.initialsystemsetup.screenbrightnessplugin"
    DESCRIPTION "KDE Initial System Setup: Screen Brightness Plugin"
    EXPORT INITIALSYSTEMSETUP
)

target_sources(screenbrightnessplugin PRIVATE
    screenbrightnessutil.cpp
    ${DBUS_SRCS}
    ${logging_SRCS}
)

target_link_libraries(screenbrightnessplugin PRIVATE
    Qt::Qml
    Qt::DBus
    Qt::Gui
    Qt::Quick
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::I18n
    KF6::Screen
)

ecm_finalize_qml_module(screenbrightnessplugin)
