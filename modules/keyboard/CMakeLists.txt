# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_qt_declare_logging_category(logging_SRCS
    HEADER "debug.h"
    IDENTIFIER "KDEInitialSystemSetup"
    CATEGORY_NAME "org.kde.initialsystemsetup.keyboard"
    DESCRIPTION "KDE Initial System Setup Keyboard Module"
    EXPORT INITIALSYSTEMSETUP
)

ecm_find_qmlmodule(org.kde.plasma.private.kcm_keyboard REQUIRED)

ecm_add_qml_module(initialstart_keyboard
    URI "org.kde.initialsystemsetup.keyboard"
    GENERATE_PLUGIN_SOURCE
    DEPENDENCIES
        Qt::Core
)

target_link_libraries(initialstart_keyboard PRIVATE
    Qt::Core
    Qt::Qml
    KF6::I18n
)

ecm_finalize_qml_module(initialstart_keyboard)
