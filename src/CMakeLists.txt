# SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_subdirectory(packagestructure)
add_subdirectory(pages)

add_executable(plasma-initialstart
    main.cpp
    pagesmodel.cpp
    pagesmodel.h
    initialstart.cpp
    initialstart.h
)

ecm_add_qml_module(plasma-initialstart GENERATE_PLUGIN_SOURCE
    URI org.kde.plasma.initialstart
)

qt_target_qml_sources(plasma-initialstart
    QML_FILES
        qml/Main.qml
)

target_link_libraries(plasma-initialstart
    PUBLIC
        Qt::Widgets
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::QuickControls2
        Qt::Svg
        KF6::I18n
        KF6::Package
)
install(TARGETS plasma-initialstart ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
