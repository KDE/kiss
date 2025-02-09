# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

ecm_add_qml_module(componentsplugin
    URI "org.kde.plasma.initialstart.components"
    GENERATE_PLUGIN_SOURCE
)

ecm_target_qml_sources(componentsplugin SOURCES
    Module.qml
)

target_link_libraries(componentsplugin PRIVATE
    Qt6::Quick
    Qt6::Qml
)

ecm_finalize_qml_module(componentsplugin DESTINATION ${KDE_INSTALL_QMLDIR})
