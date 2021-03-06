// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	required property var page

	ColumnLayout {
		anchors.centerIn: parent
		spacing: Kirigami.Units.largeSpacing * 2

		Kirigami.Heading {
			text: i18n("All Done!")
			horizontalAlignment: Text.AlignHCenter
			Layout.fillWidth: true
		}
		Image {
			source: "yay.svg"

			Layout.preferredWidth: 150
			Layout.preferredHeight: 150
		}
		Button {
			text: i18n("Let's get started")
			Layout.fillWidth: Qt.AlignHCenter

			onClicked: {
				KISS.disableSelf()
			}
		}
	}
}
