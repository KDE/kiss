# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_add_qml_module(initialstart_language
    URI "org.kde.initialsystemsetup.language"
    GENERATE_PLUGIN_SOURCE
    SOURCES
        languageutil.cpp
    DEPENDENCIES
        Qt::Core
)

target_link_libraries(initialstart_language PRIVATE
    Qt::Core
    Qt::Qml
    KF6::I18n
)

ecm_finalize_qml_module(initialstart_language)
