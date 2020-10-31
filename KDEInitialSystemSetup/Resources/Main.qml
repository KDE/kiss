import QtQuick 2.0
import QtWayland.Compositor 1.3

WaylandCompositor {
	id: waylandCompositor

	Screen {
		compositor: waylandCompositor
	}
}

