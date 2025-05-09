# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: GPL-2.0-or-later

ecm_add_qml_module(password
    URI "org.kde.initialsystemsetup.password"
    GENERATE_PLUGIN_SOURCE
)

ecm_finalize_qml_module(password DESTINATION ${KDE_INSTALL_QMLDIR})
