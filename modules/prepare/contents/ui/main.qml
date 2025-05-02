// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.initialsystemsetup.prepare.private as Prepare
import org.kde.initialsystemsetup.components as KissComponents
import org.kde.initialsystemsetup.screenbrightnessplugin as ScreenBrightness

KissComponents.SetupModule {
    id: root

    cardWidth: Math.min(Kirigami.Units.gridUnit * 30, root.contentItem.width - Kirigami.Units.gridUnit * 2)

    nextEnabled: true

    ScreenBrightness.ScreenBrightnessUtil {
        id: screenBrightness
    }

    contentItem: ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.gridUnit

            Label {
                Layout.leftMargin: Kirigami.Units.gridUnit
                Layout.rightMargin: Kirigami.Units.gridUnit
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                visible: screenBrightness.brightnessAvailable
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: i18n("Adjust the screen brightness to be comfortable for the installation process.")
            }

            FormCard.FormCard {
                id: brightnessCard
                visible: screenBrightness.brightnessAvailable
                maximumWidth: root.cardWidth

                onWidthChanged: console.log("width", this, width, root.cardWidth)

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                FormCard.AbstractFormDelegate {
                    background: null

                    contentItem: RowLayout {
                        spacing: Kirigami.Units.gridUnit

                        Kirigami.Icon {
                            implicitWidth: Kirigami.Units.iconSizes.smallMedium
                            implicitHeight: Kirigami.Units.iconSizes.smallMedium
                            source: "brightness-low"
                        }

                        Slider {
                            id: brightnessSlider
                            Layout.fillWidth: true
                            from: 1
                            to: screenBrightness.maxBrightness
                            value: screenBrightness.brightness
                            onMoved: screenBrightness.brightness = value;

                            // HACK: for some reason, the slider initial value doesn't set without being done after the component completes loading
                            Timer {
                                interval: 0
                                running: true
                                repeat: false
                                onTriggered: brightnessSlider.value = Qt.binding(() => screenBrightness.brightness)
                            }
                        }

                        Kirigami.Icon {
                            implicitWidth: Kirigami.Units.iconSizes.smallMedium
                            implicitHeight: Kirigami.Units.iconSizes.smallMedium
                            source: "brightness-high"
                        }
                    }
                }
            }

            Label {
                Layout.leftMargin: Kirigami.Units.gridUnit
                Layout.rightMargin: Kirigami.Units.gridUnit
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: i18n("Adjust the size of elements on the screen.")
            }

            FormCard.FormCard {
                id: scalingCard
                maximumWidth: root.cardWidth

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                FormCard.FormComboBoxDelegate {
                    id: displayScaling
                    text: i18n("Display Scaling")
                    displayMode: FormCard.FormComboBoxDelegate.Dialog
                    currentIndex: Prepare.PrepareUtil.scalingOptions.indexOf(Prepare.PrepareUtil.scaling.toString() + "%");
                    model: Prepare.PrepareUtil.scalingOptions

                    // remove % suffix
                    onCurrentValueChanged: Prepare.PrepareUtil.scaling = parseInt(currentValue.substring(0, currentValue.length - 1));
                }
            }

            FormCard.FormCard {
                id: darkThemeCard
                maximumWidth: root.cardWidth

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                FormCard.FormSwitchDelegate {
                    id: darkThemeSwitch
                    text: i18n("Dark Theme")
                    checked: Prepare.PrepareUtil.usingDarkTheme
                    onCheckedChanged: {
                        if (checked !== Prepare.PrepareUtil.usingDarkTheme) {
                            Prepare.PrepareUtil.usingDarkTheme = checked;
                        }
                    }
                }
            }
        }
    }
}
