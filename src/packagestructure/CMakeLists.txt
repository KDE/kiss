# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(kde_initialsystemsetup
    SOURCES kdeinitialsystemsetuppackage.cpp
    INSTALL_NAMESPACE kf6/packagestructure
)
target_link_libraries(kde_initialsystemsetup KF6::Package KF6::I18n)
