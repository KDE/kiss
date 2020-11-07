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
	property int currentPage: 0
	onCurrentPageChanged: {
		staccy.currentItem.apply()
		staccy.replace(`qrc:/pages/${KISS.pages[currentPage]}/Page.qml`)
	}

	Rectangle {
		anchors.fill: parent
		color: "#404040"
	}

	RowLayout {
		anchors {
			left: kardo.left
			right: kardo.right
			top: kardo.bottom
			topMargin: Kirigami.Units.largeSpacing
		}

		Button {
			text: "Previous"
			visible: appWindow.currentPage > 0
			onClicked: appWindow.currentPage--
		}

		Item {
			Layout.fillWidth: true
		}

		Button {
			text: "Next"
			visible: (staccy.currentItem.canNext) && (appWindow.currentPage + 1 != KISS.pages.length)
			onClicked: appWindow.currentPage++
		}
	}

	Kirigami.Card {
		id: kardo

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

				initialItem: `pages/${KISS.pages[0]}/Page.qml`

				replaceEnter: Transition {
					PropertyAnimation {
						property: "opacity"
						from: 0
						to: 1
					}
				}
				replaceExit: Transition {
					PropertyAnimation {
						property: "opacity"
						from: 1
						to: 0
					}
				}
			}
		}

	}
}
