import QtQuick 2.5
import QtQuick.Controls 2.10
import org.kde.kirigami 2.10 as Kirigami

Item {
	property string title: "User Setup"
	property string description: "Let's set up your user account"
	property bool canNext: (
		name.text !== "" &&
		user.text !== "" &&
		pass.text !== ""
	)

	function apply() {
		KISS.realname = name.text
		KISS.username = user.text
		KISS.password = pass.text
		KISS.admin = true
	}

	Kirigami.FormLayout {
		anchors.centerIn: parent

		TextField {
			id: name

			text: KISS.username

			Kirigami.FormData.label: "Realname:"
		}
		TextField {
			id: user

			text: KISS.password

			Kirigami.FormData.label: "Username:"
		}
		Kirigami.PasswordField {
			id: pass

			text: KISS.password

			Kirigami.FormData.label: "Password:"
		}
	}
}
