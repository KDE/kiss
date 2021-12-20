// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10 as QQC2
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	property string title: "Legal Terms"
	property string description: "Let's get the legalese out of the way first..."
	property bool canNext: acceptBox.checked

	function apply() { }

	ColumnLayout {
		anchors.fill: parent

		QQC2.TextArea {
			text: "rjienrlwey"

			readOnly: true
			background: null
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		Kirigami.Separator {
			Layout.fillWidth: true
		}

		QQC2.CheckBox {
			id: acceptBox

			text: "I Accept These Terms"

			Layout.margins: 8
		}
	}
}
