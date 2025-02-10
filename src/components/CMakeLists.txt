# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_library(componentsplugin STATIC)

#ecm_generate_export_header(componentsplugin
#    VERSION 1.0.0
#    BASE_NAME KirigamiAddonsStatefulApp
#    DEPRECATION_VERSIONS
#)

ecm_add_qml_module(componentsplugin
    URI "org.kde.plasma.initialstart.components"
    GENERATE_PLUGIN_SOURCE
)

target_sources(componentsplugin PRIVATE
    initialstartmodule.cpp
    initialstartmodule.h
)

target_link_libraries(componentsplugin PRIVATE
    Qt6::Quick
    Qt6::Qml
)

ecm_finalize_qml_module(componentsplugin DESTINATION ${KDE_INSTALL_QMLDIR})

#install(TARGETS componentsplugin EXPORT ${KF_INSTALL_TARGETS_DEFAULT_ARGS})
