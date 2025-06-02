# SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
# SPDX-FileCopyrightText: (C) 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.20)

project(kiss VERSION "0.1.0")

set(QT_MIN_VERSION "6.6.0")
set(KF_MIN_VERSION "6.5.0")

include(FeatureSummary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################# set KDE specific information #################
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)
include(KDEGitCommitHooks)

include(ECMDeprecationSettings)
include(ECMSetupVersion)
include(ECMGenerateExportHeader)
include(ECMPoQmTools)
include(ECMQmlModule)
include(ECMQtDeclareLoggingCategory)

################# Find dependencies #################
find_package(Qt6 ${QT_MIN_VERSION} NO_MODULE COMPONENTS Core Gui Qml QuickControls2 Svg Widgets DBus)
set_package_properties(Qt6 PROPERTIES
    TYPE REQUIRED
    PURPOSE "Required application components"
)
find_package(KF6 ${KF_MIN_VERSION} COMPONENTS I18n Package Config)
set_package_properties(KF6 PROPERTIES
    TYPE REQUIRED
    PURPOSE "Required application components"
)

if (QT_KNOWN_POLICY_QTP0004)
    qt_policy(SET QTP0004 NEW)
endif ()

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX KISS
    VERSION_HEADER ${CMAKE_CURRENT_BINARY_DIR}/kiss-version.h
)

find_package(KF6Screen CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

################# build and install #################

ecm_set_disabled_deprecation_versions(
    QT 6.8.3
    KF 6.13.0
)

add_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050d00)

add_subdirectory(src)
add_subdirectory(modules)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h modules/*.cpp modules/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

ki18n_install(po)

ecm_qt_install_logging_categories(
    EXPORT INITIALSYSTEMSETUP
    FILE initialsystemsetup.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)
