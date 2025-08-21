# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
# SPDX-License-Identifier: LGPL-2.1-or-later

ecm_qt_declare_logging_category(logging_SRCS
    HEADER "initialsystemsetup_language_debug.h"
    IDENTIFIER "KDEInitialSystemSetupLanguage"
    CATEGORY_NAME "org.kde.initialsystemsetup.language"
    DESCRIPTION "KDE Initial System Setup Language Module"
    DEFAULT_SEVERITY Debug
    EXPORT INITIALSYSTEMSETUP_LANGUAGE
)

ecm_add_qml_module(initialstart_language
    URI "org.kde.initialsystemsetup.language"
    GENERATE_PLUGIN_SOURCE
    SOURCES
        languageutil.cpp
        ${logging_SRCS}
    DEPENDENCIES
        Qt::Core
)

target_link_libraries(initialstart_language PRIVATE
    Qt::Core
    Qt::DBus
    Qt::Qml
    KF6::I18n
)

ecm_finalize_qml_module(initialstart_language)
