// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore as Core

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.kirigamiaddons.components as KirigamiComponents

import org.kde.plasma.initialstart
import org.kde.plasma.initialstart.components as InitialStartComponents

InitialStartComponents.Module {
    id: root

    nextEnabled: usernameField.text.length > 0

    contentItem: ColumnLayout {
        width: root.width
        spacing: Kirigami.Units.gridUnit

        KirigamiComponents.AvatarButton {
            id: avatar

            property FileDialog fileDialog: null

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.topMargin: Kirigami.Units.largeSpacing

            // Square button
            implicitWidth: Kirigami.Units.gridUnit * 5
            implicitHeight: implicitWidth

            padding: 0

            name: fullNameField.text

            onClicked: {
                if (fileDialog) {
                    return;
                }
                fileDialog = openFileDialog.createObject(this);
                fileDialog.chosen.connect(receivedSource => {
                    if (!receivedSource) {
                        return;
                    }
                    source = receivedSource;
                });
                fileDialog.open();
            }

            QQC2.Button {
                anchors {
                    bottom: parent.bottom
                    right: parent.right
                }
                visible: avatar.source.toString().length === 0
                icon.name: "cloud-upload"
                text: i18n("Upload new avatar")
                display: QQC2.AbstractButton.IconOnly

                onClicked: parent.clicked()

                QQC2.ToolTip.text: text
                QQC2.ToolTip.visible: hovered
                QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
            }

            QQC2.Button {
                anchors {
                    bottom: parent.bottom
                    right: parent.right
                }
                visible: avatar.source.toString().length !== 0
                icon.name: "edit-clear"
                text: i18n("Remove current avatar")
                display: QQC2.AbstractButton.IconOnly

                onClicked: avatar.source = ""

                QQC2.ToolTip.text: text
                QQC2.ToolTip.visible: hovered
                QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
            }
            Component {
                id: openFileDialog

                FileDialog {
                    currentFolder: Core.StandardPaths.standardLocations(Core.StandardPaths.PicturesLocation)[0]
                    parentWindow: root.Window.window

                    onAccepted: destroy()
                    onRejected: destroy()
                }
            }
        }


        QQC2.Label {
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            text: i18n("We need a few details to complete the setup.")

            Layout.leftMargin: Kirigami.Units.gridUnit
            Layout.rightMargin: Kirigami.Units.gridUnit
            Layout.fillWidth: true
        }

        FormCard.FormCard {
            maximumWidth: root.cardWidth

            FormCard.FormTextFieldDelegate {
                id: fullNameField

                label: i18ndc("plasma-initial-start-account", "@label:textfield", "Full Name")
                property string previousText: ''
                onTextChanged: {
                    if (usernameField.text.length === 0 || usernameField.text === previousText) {
                        usernameField.text = previousText = fullNameField.text.toLowerCase().replace(/\s/g, '');
                    }
                }

                Binding {
                    target: AccountController
                    property: 'fullName'
                    value: fullNameField.text
                }
            }
        }

        FormCard.FormCard {
            maximumWidth: root.cardWidth

            FormCard.FormTextFieldDelegate {
                id: usernameField
                label: i18ndc("plasma-initial-start-account", "@label:textfield", "Username")

                Binding {
                    target: AccountController
                    property: 'username'
                    value: usernameField.text
                }
            }

            FormCard.FormSectionText {
                text: i18nc("@info", "This will be used to name your home folder and can't be changed.")
            }
        }
    }
}
