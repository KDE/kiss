set(SOURCES
		Sources/Main.cpp
		Resources/Resources.qrc
)

add_executable(org.kde.initialsystemsetup
		${SOURCES}
)

target_compile_definitions(org.kde.initialsystemsetup
		PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_link_libraries(org.kde.initialsystemsetup
		PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 Qt5::WaylandCompositor
)

install(TARGETS org.kde.initialsystemsetup
	PERMISSIONS ${DefaultPermissions} SETUID
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)
