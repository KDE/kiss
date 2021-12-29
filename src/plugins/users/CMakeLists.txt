set(users_SOURCES
    userpage.cpp
    userpage.qrc
)
qt5_add_dbus_interface(users_SOURCES
    dbus/org.freedesktop.Accounts.Service.xml
    AccountsService
)
qt5_add_dbus_interface(users_SOURCES
    dbus/org.freedesktop.Accounts.User.xml
    User
)

kcoreaddons_add_plugin(
    page_UserPage
    SOURCES
        ${users_SOURCES}
    INSTALL_NAMESPACE
        "kisspages"
)
target_link_libraries(
    page_UserPage

PRIVATE
    Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2 Qt5::DBus
    KF5::I18n KF5::ConfigCore KF5::ConfigGui KF5::CoreAddons
    PkgConfig::Croutons
    crack
    kissplugins
)
