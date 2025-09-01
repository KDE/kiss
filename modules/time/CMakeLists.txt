# SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# 
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(initialstart_time
    URI "org.kde.initialsystemsetup.time.private"
    GENERATE_PLUGIN_SOURCE
)

target_compile_definitions(initialstart_time PRIVATE -DTRANSLATION_DOMAIN=\"plasma-initial-start-time\")

ecm_finalize_qml_module(initialstart_time DESTINATION ${KDE_INSTALL_QMLDIR})
