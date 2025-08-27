// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore as Core

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.kirigamiaddons.components as KirigamiComponents

import org.kde.initialsystemsetup
import org.kde.initialsystemsetup.components as KissComponents

KissComponents.SetupModule {
    id: root

    nextEnabled: usernameField.text.length > 0 && paswordField.text.length > 0 && repeatField.text === paswordField.text

    contentItem: ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            anchors.fill: parent
            spacing: Kirigami.Units.mediumSpacing

            KirigamiComponents.AvatarButton {
                id: avatar

                property FileDialog fileDialog: null

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

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

                Button {
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                    }
                    visible: avatar.source.toString().length === 0
                    icon.name: "cloud-upload"
                    text: i18n("Upload new avatar")
                    display: AbstractButton.IconOnly

                    onClicked: parent.clicked()

                    ToolTip.text: text
                    ToolTip.visible: hovered
                    ToolTip.delay: Kirigami.Units.toolTipDelay
                }

                Button {
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                    }
                    visible: avatar.source.toString().length !== 0
                    icon.name: "edit-clear"
                    text: i18n("Remove current avatar")
                    display: AbstractButton.IconOnly

                    onClicked: avatar.source = ""

                    ToolTip.text: text
                    ToolTip.visible: hovered
                    ToolTip.delay: Kirigami.Units.toolTipDelay
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

            // Padding around the text
            Item {
                Layout.topMargin: Kirigami.Units.gridUnit
            }

            Label {
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: i18n("We need a few details to complete the setup.")

                Layout.leftMargin: Kirigami.Units.gridUnit
                Layout.rightMargin: Kirigami.Units.gridUnit
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter

                Label {
                    text: i18nc("@info", "This user will be an administrator.")
                }

                Kirigami.ContextualHelpButton {
                    toolTipText: xi18nc("@info", "This user will have administrative privileges on the system.<nl/><nl/>This means that they can change system settings, install software, and access all files on the system.<nl/><nl/>Choose a strong password for this user.")
                }
            }

            // Padding around the text
            Item {
                Layout.bottomMargin: Kirigami.Units.gridUnit
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormTextFieldDelegate {
                    id: fullNameField

                    label: i18nc("@label:textfield", "Full Name")
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
                    label: i18nc("@label:textfield", "Username")

                    Binding {
                        target: AccountController
                        property: 'username'
                        value: usernameField.text
                    }
                }
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormPasswordFieldDelegate {
                    id: paswordField

                    label: i18nc("@label:textfield", "Password")

                    onTextChanged: {
                        showPasswordQuality = text.length > 0;
                    }
                }
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormPasswordFieldDelegate {
                    id: repeatField
                    label: i18nc("@label:textfield", "Confirm Password")
                    status: Kirigami.MessageType.Error

                    function setPasswordMatchError() {
                        repeatField.statusMessage = i18nc("@info:status", "Passwords don’t match");
                        repeatField.status = Kirigami.MessageType.Error;
                    }

                    function clearPasswordMatchError() {
                        repeatField.statusMessage = '';
                        repeatField.status = Kirigami.MessageType.Information;
                    }

                    // Timer delays validation while the user is typing.
                    Timer {
                        id: validationTimer
                        interval: Kirigami.Units.humanMoment
                        running: false
                        repeat: false

                        onTriggered: {
                            if (repeatField.text.length > 0 && repeatField.text !== paswordField.text) {
                                repeatField.setPasswordMatchError();
                            } else {
                                repeatField.clearPasswordMatchError();
                            }
                        }
                    }

                    // Reset timer when the user types.
                    onTextChanged: {
                        // If passwords match, immediately clear the error message.
                        if (text.length > 0 && text === paswordField.text) {
                            repeatField.clearPasswordMatchError();
                        } else {
                            validationTimer.restart();
                        }
                    }

                    onEditingFinished: function () {
                        if (text.length < 1 || text !== paswordField.text) {
                            repeatField.setPasswordMatchError();
                        } else {
                            repeatField.clearPasswordMatchError();
                            AccountController.password = text;
                            return;
                        }
                    }
                }
            }
        }
    }
}
