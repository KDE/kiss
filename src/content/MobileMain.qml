// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
	property int oldPage: 0
	property bool goingForward: true
	onCurrentPageChanged: {
		if (oldPage < currentPage) {
			goingForward = true
		} else {
			goingForward = false
		}
		oldPage = currentPage
		staccy.currentItem.apply()
		staccy.replace(`qrc:${KISS.pages[currentPage]}.qml`)
	}

	Rectangle {
		anchors.fill: parent
		color: PlasmaCore.ColorScope.backgroundColor
	}

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

			Behavior on implicitHeight {
				NumberAnimation {
					duration: Kirigami.Units.shortDuration
					easing.type: Easing.InOutCirc
				}
			}

			contentItem: ColumnLayout {
				Kirigami.Heading {
					text: staccy.currentItem.title ?? "yeet"
					horizontalAlignment: Text.AlignHCenter

					Layout.fillWidth: true
				}
				Kirigami.Heading {
					opacity: text !== "" ? 0.7 : 0
					Layout.preferredHeight: text !== "" ? -1 : 0

					text: staccy.currentItem.description ?? ""
					horizontalAlignment: Text.AlignHCenter
					level: 4

					Behavior on opacity {
						NumberAnimation {
							duration: Kirigami.Units.shortDuration
							easing.type: Easing.InOutCirc
						}
					}

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

			initialItem: `${KISS.pages[0]}.qml`
			property real aniFrom: (staccy.mirrored ? -1 : 1) * staccy.width
			property real aniTo: (staccy.mirrored ? -1 : 1) * -staccy.width

			replaceEnter: Transition {
				XAnimator {
					from: appWindow.goingForward ? staccy.aniFrom : staccy.aniTo
					to: 0
					duration: Kirigami.Units.shortDuration
					easing.type: Easing.InOutCirc
				}
			}

			replaceExit: Transition {
				XAnimator {
					from: 0
					to: appWindow.goingForward ? staccy.aniTo : staccy.aniFrom
					duration: Kirigami.Units.shortDuration
					easing.type: Easing.InOutCirc
				}
			}
		}
		PE.PlasmoidHeading {
			Layout.leftMargin: -leftInset
			Layout.rightMargin: -rightInset
			Layout.bottomMargin: -bottomInset
			Layout.topMargin: -topInset

			location: PE.PlasmoidHeading.Footer

			contentItem: RowLayout {
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
		}
	}
}
