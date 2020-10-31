import QtQuick 2.5
import QtQuick.Controls 2.15
import org.kde.kirigami 2.10 as Kirigami

ApplicationWindow {
	id: appWindow
	visible: true

	property string language: ""

	Component {
		id: userPage

		Item {
			Kirigami.FormLayout {
				anchors.centerIn: parent

				TextField {
					id: name
				}
				TextField {
					id: user
				}
				TextField {
					id: pass
				}
				Button {
					text: "clicc"

					onClicked: {
						KISS.createAccount(name.text, user.text, pass.text, false, appWindow.language)
					}
				}
			}
		}
	}

	StackView {
		id: staccy
		anchors.fill: parent

		initialItem: ListView {
			model: KISS.locales

			delegate: Kirigami.BasicListItem {
				text: modelData

				onClicked: {
					appWindow.language = modelData
					staccy.push(userPage)
				}
			}
		}
	}
}
