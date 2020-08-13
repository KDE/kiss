# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: LGPL-2.0-or-later

set_source_files_properties(org.freedesktop.Accounts.xml PROPERTIES NO_NAMESPACE TRUE)
set_source_files_properties(org.freedesktop.Accounts.User.xml PROPERTIES NO_NAMESPACE TRUE)

qt_add_dbus_interface(initialstart_account_DBUS_SRCS
    org.freedesktop.Accounts.xml
    accounts_interface
)

qt_add_dbus_interface(initialstart_account_DBUS_SRCS
    org.freedesktop.Accounts.User.xml
    user_interface
)

ecm_add_qml_module(initialstart_account
    URI "org.kde.plasma.initialstart.account.private"
    GENERATE_PLUGIN_SOURCE
)

target_sources(initialstart_account PRIVATE
    accountcontroller.cpp
    accountcontroller.h
    ${initialstart_account_DBUS_SRCS}
)

target_compile_definitions(initialstart_account PRIVATE -DTRANSLATION_DOMAIN=\"plasma-initial-start-account\")

target_link_libraries(initialstart_account PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::DBus
    KF6::I18n
    KF6::I18n
    KF6::CoreAddons
)

ecm_finalize_qml_module(initialstart_account DESTINATION ${KDE_INSTALL_QMLDIR})
