import QtQuick 2.5
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.5
import QtQuick.Window 2.2
import QtWayland.Compositor 1.0

WaylandOutput {
	id: output

	property bool isNestedCompositor: Qt.platform.pluginName.startsWith("wayland") || Qt.platform.pluginName === "xcb"
	sizeFollowsWindow: output.isNestedCompositor

	window: Window {
		id: window

		width: 1024
		height: 760
		visible: true

		Rectangle {
			anchors.fill: parent

			color: "cyan"
		}
	}
}
