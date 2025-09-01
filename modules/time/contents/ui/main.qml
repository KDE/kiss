// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.initialsystemsetup.time.private as Time

import org.kde.initialsystemsetup
import org.kde.initialsystemsetup.components as KissComponents

KissComponents.SetupModule {
    id: root

    contentItem: ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            anchors.centerIn: parent
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
                    checked: TimeUtil.is24HourTime
                    onCheckedChanged: {
                        if (checked !== TimeUtil.is24HourTime) {
                            TimeUtil.is24HourTime = checked;
                        }
                    }
                }
            }

            ColumnLayout {
                Kirigami.SearchField {
                    id: searchField
                    Layout.fillWidth: true

                    onTextChanged: {
                        TimeUtil.timeZones.filterString = text;
                    }
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.minimumHeight: Kirigami.Units.gridUnit * 14
                    Layout.maximumHeight: Kirigami.Units.gridUnit * 20

                    Component.onCompleted: {
                        if (background) {
                            background.visible = true;
                        }
                    }

                    ListView {
                        id: listView

                        clip: true
                        model: TimeUtil.timeZones
                        currentIndex: -1 // ensure focus is not on the listview

                        bottomMargin: 2

                        delegate: FormCard.FormRadioDelegate {
                            required property string timeZoneId

                            width: ListView.view.width
                            text: timeZoneId
                            checked: TimeUtil.currentTimeZone === timeZoneId
                            onToggled: {
                                if (checked && timeZoneId !== TimeUtil.currentTimeZone) {
                                    TimeUtil.currentTimeZone = timeZoneId;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
