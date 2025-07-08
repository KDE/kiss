# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

ecm_qt_declare_logging_category(logging_SRCS
    HEADER "initialsystemsetup_bootutil_debug.h"
    IDENTIFIER "KDEInitialSystemSetupBootUtil"
    CATEGORY_NAME "org.kde.initialsystemsetup.bootutil"
    DESCRIPTION "KDE Initial System Setup Boot Utility"
    EXPORT INITIALSYSTEMSETUP_BOOTUTIL
)

add_executable(kde-initial-system-setup-bootutil
    bootutil.cpp
    bootutil.h
    main.cpp
    ${logging_SRCS}
)

target_link_libraries(kde-initial-system-setup-bootutil
    Qt::Core
)

install(TARGETS kde-initial-system-setup-bootutil RUNTIME DESTINATION ${KDE_INSTALL_LIBEXECDIR})
