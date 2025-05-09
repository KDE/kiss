# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_add_qml_module(account
    URI "org.kde.initialsystemsetup.account"
    GENERATE_PLUGIN_SOURCE
)

ecm_finalize_qml_module(account DESTINATION ${KDE_INSTALL_QMLDIR})
