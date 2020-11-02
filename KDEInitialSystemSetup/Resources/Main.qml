import QtQuick 2.5
import QtQuick.Controls 2.15
import org.kde.kirigami 2.10 as Kirigami

ApplicationWindow {
	id: appWindow
	visible: true

	property string language: ""

	StackView {
		id: staccy
		anchors.fill: parent

		initialItem: "pages/locale/Page.qml"
	}
}
