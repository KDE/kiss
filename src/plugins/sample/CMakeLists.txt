set(sample_SOURCES
    samplepage.cpp
    samplepage.qrc
)

kcoreaddons_add_plugin(
    page_SamplePage
    SOURCES
        ${sample_SOURCES}
    INSTALL_NAMESPACE
        "kisspages"
)
target_link_libraries(
    page_SamplePage

PRIVATE
    Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickControls2
    KF5::I18n KF5::ConfigCore KF5::ConfigGui KF5::CoreAddons

    kissplugins
)
