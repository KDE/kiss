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

    nextEnabled: paswordField.text.length > 0 && repeatField.text === paswordField.text

    contentItem: ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.gridUnit

            Label {
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: i18n("Be careful not to lose your password.")

                Layout.leftMargin: Kirigami.Units.gridUnit
                Layout.rightMargin: Kirigami.Units.gridUnit
                Layout.fillWidth: true
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormPasswordFieldDelegate {
                    id: paswordField

                    label: i18ndc("plasma-initial-start-account", "@label:textfield", "Password")

                    Component.onCompleted: showPasswordQuality = true
                }
            }

            FormCard.FormCard {
                maximumWidth: root.cardWidth

                FormCard.FormPasswordFieldDelegate {
                    id: repeatField
                    label: i18ndc("plasma-initial-start-account", "@label:textfield", "Confirm Password")
                    statusMessage: text.length > 0 && text !== paswordField.text ? i18nc("@info:status", "The passwords do not match.") : ''
                    status: Kirigami.MessageType.Error
                }
            }
        }
    }
}
