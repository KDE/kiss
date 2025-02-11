// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.plasma.initialstart.time.private as Time

import org.kde.plasma.initialstart.components as InitialStartComponents

InitialStartComponents.Module {
    id: root

    contentItem: ColumnLayout {
        spacing: Kirigami.Units.gridUnit

        Label {
            Layout.leftMargin: Kirigami.Units.gridUnit
            Layout.rightMargin: Kirigami.Units.gridUnit
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: i18n("Select your time zone and preferred time format.")
        }

        FormCard.FormCard {
            maximumWidth: root.cardWidth

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true

            FormCard.FormSwitchDelegate {
                Layout.fillWidth: true
                text: i18n("24-Hour Format")
                checked: Time.TimeUtil.is24HourTime
                onCheckedChanged: {
                    if (checked !== Time.TimeUtil.is24HourTime) {
                        Time.TimeUtil.is24HourTime = checked;
                    }
                }
            }
        }

        FormCard.FormCard {
            maximumWidth: root.cardWidth

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true

            Control {
                Layout.fillWidth: true

                leftPadding: Kirigami.Units.largeSpacing
                rightPadding: Kirigami.Units.largeSpacing
                topPadding: Kirigami.Units.largeSpacing
                bottomPadding: Kirigami.Units.largeSpacing

                contentItem: Kirigami.SearchField {
                    id: searchField

                    onTextChanged: {
                        Time.TimeUtil.timeZones.filterString = text;
                    }
                }
            }

            Kirigami.Separator {
                Layout.fillWidth: true
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: Kirigami.Units.gridUnit * 10
                Layout.maximumHeight: Kirigami.Units.gridUnit * 10

                ListView {
                    id: listView

                    clip: true
                    model: Time.TimeUtil.timeZones
                    currentIndex: -1 // ensure focus is not on the listview

                    bottomMargin: 2

                    delegate: FormCard.FormRadioDelegate {
                        required property string timeZoneId

                        width: ListView.view.width
                        text: timeZoneId
                        checked: Time.TimeUtil.currentTimeZone === timeZoneId
                        onToggled: {
                            if (checked && timeZoneId !== Time.TimeUtil.currentTimeZone) {
                                Time.TimeUtil.currentTimeZone = timeZoneId;
                                checked = Qt.binding(() => Time.TimeUtil.currentTimeZone === timeZoneId);
                            }
                        }
                    }
                }
            }
        }
    }
}
