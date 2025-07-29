// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore as Core

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.kirigamiaddons.components as KirigamiComponents
import org.kde.initialsystemsetup.components as KissComponents

import org.kde.initialsystemsetup

KissComponents.SetupModule {
    id: root

    contentItem: ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.gridUnit

            RowLayout {
                Layout.alignment: Qt.AlignHCenter

                Label {
                    text: i18nc("@info", "This user will be an administrator.")
                }

                Kirigami.ContextualHelpButton {
                    toolTipText: xi18nc("@info", "This user will have administrative privileges on the system.<nl/><nl/>This means that they can change system settings, install software, and access all files on the system.<nl/><nl/>Choose a strong password for this user.")

                }
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormPasswordFieldDelegate {
                    id: paswordField

                    label: i18nc("@label:textfield", "Password")

                    Component.onCompleted: showPasswordQuality = true
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

                    onEditingFinished: function() {
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

    nextEnabled: paswordField.text.length > 0 && repeatField.text === paswordField.text
}
