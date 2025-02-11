# SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(initialstart_time
    URI "org.kde.plasma.initialstart.time.private"
    GENERATE_PLUGIN_SOURCE
)

set_source_files_properties(org.freedesktop.timedate1.xml PROPERTIES NO_NAMESPACE TRUE)

qt_add_dbus_interface(initialstart_time_DBUS_SRCS
    org.freedesktop.timedate1.xml
    timedate_interface
)

target_sources(initialstart_time PRIVATE
    timeutil.cpp
    timeutil.h
    timezonemodel.cpp
    timezonemodel.h
    ${initialstart_time_DBUS_SRCS}
)

target_link_libraries(initialstart_time PUBLIC
    Qt::Core
    Qt::DBus
    Qt::Quick
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::I18n
)

target_compile_definitions(initialstart_time PRIVATE -DTRANSLATION_DOMAIN=\"plasma-initial-start-time\")

ecm_finalize_qml_module(initialstart_time DESTINATION ${KDE_INSTALL_QMLDIR})
