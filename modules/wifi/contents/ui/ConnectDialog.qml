// SPDX-FileCopyrightText: 2020-2024 Devin Lin <espidev@gmail.com>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.components as Components
import org.kde.plasma.networkmanagement as PlasmaNM

Components.MessageDialog {
    id: root

    title: headingText

    property int securityType
    property string headingText
    property string devicePath
    property string specificPath
    property PlasmaNM.Handler handler

    signal donePressed(string password)

    function openAndClear(): void {
        this.open();
        passwordField.text = "";
        passwordField.focus = true;
    }

    implicitWidth: Math.min(parent.width - Kirigami.Units.gridUnit * 2, Kirigami.Units.gridUnit * 22)

    iconName: 'dialog-password'

    standardButtons: Controls.Dialog.Ok | Controls.Dialog.Cancel

    onOpened: passwordField.forceActiveFocus()
    onRejected: {
        root.close();
        passwordField.focus = false;
    }
    onAccepted: {
        if (passwordField.acceptableInput) {
            root.close();
            root.handler.addAndActivateConnection(devicePath, specificPath, passwordField.text, PlasmaNM.Handler.StoreForAllUsers);
        }
        passwordField.focus = false;
    }

    PasswordField {
        id: passwordField
        Layout.fillWidth: true
        securityType: root.securityType
        onAccepted: root.accept()
    }
}
