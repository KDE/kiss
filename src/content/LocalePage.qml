// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

ListView {
	model: KISS.locales

	required property var page

	delegate: Kirigami.BasicListItem {
		text: modelData.name

		property string code: modelData.code

		onClicked: {
			KISS.targetLanguage = modelData.code
			appWindow.currentPage++
		}
	}
}
