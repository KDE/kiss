# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(plasma_initialstart
    SOURCES plasmainitialstartpackage.cpp
    INSTALL_NAMESPACE kf6/packagestructure
)
target_link_libraries(plasma_initialstart KF6::Package KF6::I18n)