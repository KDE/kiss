// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

import org.kde.initialsystemsetup.components as InitialStartComponents
import org.kde.initialsystemsetup

InitialStartComponents.Module {
    id: root

    nextEnabled: true

    contentItem: ColumnLayout {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.gridUnit

        Label {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: i18n("Your device is now ready. <br /><br />Enjoy <b>%1</b>!", InitialStartUtil.distroName)
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
        }

        Item { Layout.fillHeight: true }

        Image {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            fillMode: Image.PreserveAspectFit
            source: "konqi-calling.png"
        }
    }
}
