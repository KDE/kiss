// SPDX-FileCopyrightText: 2017 Martin Kacej <m.kacej@atlas.sk>
// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.plasma.networkmanagement as PlasmaNM

import org.kde.initialsystemsetup.components as KissComponents

KissComponents.SetupModule {
    id: root

    available: availableDevices.wirelessDeviceAvailable

    contentItem: ColumnLayout {
        spacing: Kirigami.Units.gridUnit

        PlasmaNM.AvailableDevices {
            id: availableDevices
        }

        PlasmaNM.Handler {
            id: handler
        }

        PlasmaNM.EnabledConnections {
            id: enabledConnections
        }

        PlasmaNM.NetworkModel {
            id: connectionModel
        }

        PlasmaNM.MobileProxyModel {
            id: mobileProxyModel
            sourceModel: connectionModel
            showSavedMode: false
        }

        ConnectDialog {
            id: connectionDialog
            handler: handler
            parent: root.contentItem.Overlay.overlay
        }

        Component.onCompleted: handler.requestScan()

        Timer {
            id: scanTimer
            interval: 10200
            repeat: true
            running: parent.visible

            onTriggered: handler.requestScan()
        }

        Label {
            Layout.leftMargin: Kirigami.Units.gridUnit
            Layout.rightMargin: Kirigami.Units.gridUnit
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: i18n("Connect to a WiFi network for network access.")
        }

        FormCard.FormCard {
            id: savedCard
            maximumWidth: root.cardWidth
            visible: enabledConnections.wirelessEnabled && count > 0

            // number of visible entries
            property int count: 0
            function updateCount() {
                count = 0;
                for (let i = 0; i < connectedRepeater.count; i++) {
                    let item = connectedRepeater.itemAt(i);
                    if (item && item.shouldDisplay) {
                        count++;
                    }
                }
            }

            Repeater {
                id: connectedRepeater
                model: mobileProxyModel
                delegate: ConnectionItemDelegate {
                    // connected or saved
                    property bool shouldDisplay: (Uuid != "") || ConnectionState === PlasmaNM.Enums.Activated
                    onShouldDisplayChanged: savedCard.updateCount()

                    // separate property for visible since visible is false when the whole card is not visible
                    visible: (Uuid != "") || ConnectionState === PlasmaNM.Enums.Activated
                }
            }
        }

        FormCard.FormCard {
            Layout.fillHeight: true
            maximumWidth: root.cardWidth
            visible: enabledConnections.wirelessEnabled

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: Kirigami.Units.gridUnit * 14
                Layout.maximumHeight: Kirigami.Units.gridUnit * 14

                ListView {
                    id: listView

                    clip: true
                    model: mobileProxyModel

                    delegate: ConnectionItemDelegate {
                        width: ListView.view.width
                        height: visible ? implicitHeight : 0
                        visible: !((Uuid != "") || ConnectionState === PlasmaNM.Enums.Activated)
                    }
                }
            }
        }
    }
}
