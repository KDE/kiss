# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(wifi
    URI "org.kde.initialsystemsetup.wifi"
    GENERATE_PLUGIN_SOURCE
)

ecm_finalize_qml_module(wifi DESTINATION ${KDE_INSTALL_QMLDIR})
