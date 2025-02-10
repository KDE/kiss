# SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(initialstart_prepare
    URI "org.kde.plasma.initialstart.prepare.private"
    GENERATE_PLUGIN_SOURCE
)

kconfig_add_kcfg_files(initialstart_prepare colorssettings.kcfgc GENERATE_MOC)

target_sources(initialstart_prepare PRIVATE
    ${prepareplugin_SRCS}
    prepareutil.cpp
    prepareutil.h
)

target_link_libraries(initialstart_prepare PRIVATE
    Qt::Core
    Qt::DBus
    Qt::Quick
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::I18n
    KF6::Screen
)

target_compile_definitions(initialstart_prepare PRIVATE -DTRANSLATION_DOMAIN=\"plasma-initial-start-prepare\")

ecm_finalize_qml_module(initialstart_prepare DESTINATION ${KDE_INSTALL_QMLDIR})
