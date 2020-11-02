import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	Kirigami.FormLayout {
		anchors.centerIn: parent

		TextField {
			id: name

			Kirigami.FormData.label: "Realname:"
		}
		TextField {
			id: user

			Kirigami.FormData.label: "Username:"
		}
		Kirigami.PasswordField {
			id: pass

			Kirigami.FormData.label: "Password:"
		}
		Button {
			text: "create user"

			onClicked: {
				KISS.createAccount(name.text, user.text, pass.text, true, appWindow.language)
			}
		}
	}
}
