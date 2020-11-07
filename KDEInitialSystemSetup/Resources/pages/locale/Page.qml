import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

ListView {
	model: KISS.locales
	property string title: "Welcome"
	property string description: "Select a language to begin setup"
	property bool canNext: true

	function apply() {
		KISS.targetLanguage = currentItem.code
	}

	delegate: Kirigami.BasicListItem {
		text: modelData.name

		property string code: modelData.code

		onClicked: {
			KISS.targetLanguage = modelData.code
			appWindow.currentPage++
		}
	}
}
