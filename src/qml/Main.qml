// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.delegates as Delegates
import org.kde.plasma.initialstart

Kirigami.AbstractApplicationWindow {
    id: root

    title: i18n("Initial Start")

    visibility: "Windowed"

    Wizard {
        anchors.fill: parent
    }


    /*ColumnLayout {
        spacing: 0
        anchors.fill: parent

        Controls.ToolBar {
            Layout.fillWidth: true

            contentItem: Kirigami.Heading {
                text: root.title
            }
        }

        Controls.StackView {
            id: stackView

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }*/
}
