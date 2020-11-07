import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

ListView {
	model: KISS.locales
	property string title: "Welcome"
	property string description: "Select a language to begin setup"

	delegate: Kirigami.BasicListItem {
		text: modelData.name

		onClicked: {
			appWindow.language = modelData.code
			staccy.push("qrc:/pages/user/Page.qml")
		}
	}
}
