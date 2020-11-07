import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.12 as Kirigami
import org.kde.plasma.extras 2.0 as PE
import org.kde.plasma.core 2.0 as PlasmaCore

ApplicationWindow {
	id: appWindow
	visible: true

	property string language: ""

	Rectangle {
		anchors.fill: parent
		color: "#404040"
	}

	Kirigami.Card {
		height: parent.height > Kirigami.Units.gridUnit * 30 ? Kirigami.Units.gridUnit * 30 : parent.height
		width: parent.width > Kirigami.Units.gridUnit * 20 ? Kirigami.Units.gridUnit * 20 : parent.width

		anchors.centerIn: parent

		ColumnLayout {
			anchors.fill: parent
			spacing: 0

			QtObject {
				id: plasmoid
				property int location: PlasmaCore.Types.TopEdge
			}

			PE.PlasmoidHeading {
				Layout.leftMargin: -leftInset
				Layout.rightMargin: -rightInset
				Layout.bottomMargin: -bottomInset
				Layout.topMargin: -topInset

				contentItem: ColumnLayout {
					Kirigami.Heading {
						text: staccy.currentItem.title ?? "yeet"
						horizontalAlignment: Text.AlignHCenter

						Layout.fillWidth: true
					}
					Kirigami.Heading {
						visible: text !== ""

						text: staccy.currentItem.description ?? ""
						horizontalAlignment: Text.AlignHCenter
						level: 4
						opacity: 0.7

						Layout.fillWidth: true
					}
				}
			}
			StackView {
				id: staccy

				Layout.fillHeight: true
				Layout.fillWidth: true
				Layout.leftMargin: 1
				Layout.rightMargin: 1
				Layout.bottomMargin: 1

				clip: true

				initialItem: "pages/locale/Page.qml"
			}
		}

	}

	Connections {
		target: KISS
		function onFinished(success) {
			if (success) {
				staccy.replace("qrc:/pages/ready/Page.qml")
			}
		}
	}
}
