add_library(kissplugins SHARED
    ipage.cpp
    pageloader.cpp
)

target_link_libraries(kissplugins
	PUBLIC
		Qt5::Core Qt5::Quick Qt5::QuickControls2
		KF5::CoreAddons
		PkgConfig::Croutons
)
target_include_directories(kissplugins
    PUBLIC
        .
)

install(TARGETS kissplugins
	DESTINATION ${KDE_INSTALL_LIBDIR}
)
