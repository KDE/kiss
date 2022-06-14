set(license_SOURCES
	licensepage.cpp
	licensepage.qrc
)

kcoreaddons_add_plugin(
	page_LicensePage
	SOURCES
		${license_SOURCES}
	INSTALL_NAMESPACE
		"kisspages"
)

kconfig_add_kcfg_files(page_LicensePage initialsystemsetuplicense.kcfgc)

target_link_libraries(
	page_LicensePage

PRIVATE
	Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2 Qt5::DBus
	KF5::I18n KF5::ConfigCore KF5::ConfigGui KF5::CoreAddons
	PkgConfig::Croutons
	crack
	kissplugins
)
