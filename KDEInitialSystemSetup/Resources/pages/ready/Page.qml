import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	property string title: ""
	property bool canNext: false

	function apply() {}

	ColumnLayout {
		anchors.centerIn: parent

		Kirigami.Heading {
			text: "All Done!"
		}
		Button {
			text: "Let's get started"

			onClicked: {
				KISS.disableSelf()
			}
		}
	}
}
