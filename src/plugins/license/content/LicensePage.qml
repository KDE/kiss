// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

ColumnLayout {
	id: _root

	required property var page

	ScrollView {
		id: scrollView

		ScrollBar.vertical.policy: ScrollBar.AlwaysOn
		ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

		Flickable {
			contentWidth: textArea.width
			contentHeight: textArea.implicitHeight

			TextArea {
				id: textArea
				width: scrollView.width - scrollView.ScrollBar.vertical.width

				wrapMode: Text.Wrap
				text: _root.page.licenseText
				textFormat: _root.page.textFormat

				readOnly: true
				background: null
			}
		}

		Layout.fillWidth: true
		Layout.fillHeight: true
	}

	Kirigami.Separator {
		Layout.fillWidth: true
	}

	CheckBox {
		text: i18n("I accept these terms and conditions")
		onToggled: _root.page.setCanGoNext(checked)
		Layout.margins: Kirigami.Units.largeSpacing
	}
}
