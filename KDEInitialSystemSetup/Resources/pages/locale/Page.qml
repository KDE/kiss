import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

ListView {
	model: KISS.locales

	delegate: Kirigami.BasicListItem {
		text: modelData

		onClicked: {
			appWindow.language = modelData
			staccy.push("qrc:/pages/user/Page.qml")
		}
	}
}
