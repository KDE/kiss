# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_find_qmlmodule(org.kde.plasma.private.kcm_keyboard REQUIRED)

ecm_add_qml_module(initialstart_keyboard
    URI "org.kde.initialsystemsetup.keyboard"
    GENERATE_PLUGIN_SOURCE
    SOURCES
        keyboardutil.cpp
    DEPENDENCIES
        Qt::Core
)

target_link_libraries(initialstart_keyboard PRIVATE
    Qt::Core
    Qt::Qml
    KF6::I18n
)

ecm_finalize_qml_module(initialstart_keyboard)
