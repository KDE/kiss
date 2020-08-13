// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.plasma.initialstart.account.private

FormCard.FormCardPage {
    id: root

    AccountController {
        id: accountController

    }

    FormCard.FormCard {
        Layout.topMargin: Kirigami.Units.gridUnit

        FormCard.FormTextFieldDelegate {
            label: i18ndc("plasma-initial-start-account", "@label:textfield", "Full Name")
            onTextChanged: accountController.fullName = text;
        }

        FormCard.FormDelegateSeparator {}

        FormCard.FormTextFieldDelegate {
            label: i18ndc("plasma-initial-start-account", "@label:textfield", "Username")
            onTextChanged: accountController.username = text;
        }
    }
}
