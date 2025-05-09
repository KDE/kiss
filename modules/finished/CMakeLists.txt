# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_add_qml_module(finished
    URI "org.kde.initialsystemsetup.finished"
    GENERATE_PLUGIN_SOURCE
)

ecm_finalize_qml_module(finished DESTINATION ${KDE_INSTALL_QMLDIR})
