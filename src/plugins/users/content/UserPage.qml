// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	id: _root

	required property var page

	Kirigami.FormLayout {
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: parent.left
		anchors.right: parent.right

		TextField {
			id: name

			text: _root.page.dataStore.realname || ""
            onTextChanged: _root.page.dataStore.realname = text

			Kirigami.FormData.label: "Realname:"
		}
		TextField {
			id: user

			text: _root.page.dataStore.username || ""
            onTextChanged: _root.page.dataStore.username = text

			Kirigami.FormData.label: "Username:"
		}
		Kirigami.PasswordField {
			id: pass

			text: _root.page.dataStore.password || ""
            onTextChanged: _root.page.dataStore.password = text

			Kirigami.FormData.label: "Password:"
		}
		Kirigami.InlineMessage {
			text: _root.page.checkPassword(user.text, name.text, pass.text)
			type: Kirigami.MessageType.Error
			visible: pass.text !== "" && text !== ""

			Layout.fillWidth: true
			Layout.column: 1
			Layout.columnSpan: 2
			Kirigami.FormData.isSection: true
		}
	}
}
