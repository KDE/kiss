// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

ScrollView {
	id: root

	required property var page

	ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

	ListView {
		model: root.page.locales

		delegate: Kirigami.BasicListItem {
			text: modelData.name

			property string code: modelData.code

			onClicked: {
				root.page.dataStore.targetLanguage = modelData.code
			}
		}
	}
}
