# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_library(componentsplugin STATIC)

ecm_add_qml_module(componentsplugin
    URI "org.kde.initialsystemsetup.components"
    GENERATE_PLUGIN_SOURCE
    DEPENDENCIES
        QtQuick
)

target_sources(componentsplugin PRIVATE
    setupmodule.cpp
    setupmodule.h
)

target_link_libraries(componentsplugin PRIVATE
    Qt6::Quick
    Qt6::Qml
)

ecm_finalize_qml_module(componentsplugin DESTINATION ${KDE_INSTALL_QMLDIR})
