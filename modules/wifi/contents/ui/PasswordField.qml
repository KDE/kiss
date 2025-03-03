// SPDX-FileCopyrightText: 2013-2017 Jan Grulich <jgrulich@redhat.com>
// SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL

import QtQuick
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.plasma.networkmanagement as PlasmaNM

FormCard.FormPasswordFieldDelegate {
    id: root

    property int securityType

    label: i18n("Password:")
    validator: RegularExpressionValidator {
        regularExpression: if (securityType == PlasmaNM.Enums.StaticWep) {
            return /^(?:.{5}|[0-9a-fA-F]{10}|.{13}|[0-9a-fA-F]{26}){1}$/;
        } else {
            return /^(?:.{8,64}){1}$/;
        }
    }

    leftPadding: 0
    rightPadding: 0

    onAccepted: statusMessage = acceptableInput ? '' : i18n("Invalid input.");
    status: Kirigami.MessageType.Error
}

