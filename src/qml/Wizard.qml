// SPDX-FileCopyrightText: 2023 Devin Lin <devin@kde.org>
// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.initialsystemsetup
import org.kde.initialsystemsetup.components as KissComponents

Kirigami.Page {
    id: root

    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0

    property int currentIndex: -1
    readonly property int stepCount: stepsRepeater.count
    property bool showingLanding: true

    // filled by items
    property Control currentStepItem: null
    property Control nextStepItem: null
    property Control previousStepItem: null
    property KissComponents.SetupModule currentModule: null

    readonly property bool onFinalPage: currentIndex === (stepCount - 1)

    // step animation
    // manually doing the animation is more performant and less glitchy with window resize than a SwipeView
    property real previousStepItemX: 0
    property real currentStepItemX: 0
    property real nextStepItemX: 0

    NumberAnimation on previousStepItemX {
        id: previousStepAnim
        duration: 400
        easing.type: Easing.OutExpo
        onFinished: {
            if (root.previousStepItemX != 0) {
                root.previousStepItem.visible = false;
            }
        }
    }

    NumberAnimation on currentStepItemX {
        id: currentStepAnim
        duration: 400
        easing.type: Easing.OutExpo
    }

    NumberAnimation on nextStepItemX {
        id: nextStepAnim
        duration: 400
        easing.type: Easing.OutExpo
        onFinished: {
            if (root.nextStepItemX != 0) {
                root.nextStepItem.visible = false;
            }
        }
    }

    onStepCountChanged: {
        // reset position
        requestPreviousPage();
    }

    function finishFinalPage(): void {
        AccountController.createUser();
        // the app exits
        InitialStart.Wizard.wizardFinished();
    }

    function requestNextPage(): void {
        if (previousStepAnim.running || currentStepAnim.running || nextStepAnim.running) {
            return;
        }

        previousStepItemX = 0;

        currentIndex++;
        stepHeading.changeText(currentStepItem.name);

        currentStepItemX = root.width;
        currentStepItem.visible = true;

        previousStepAnim.to = -root.width;
        previousStepAnim.restart();
        currentStepAnim.to = 0;
        currentStepAnim.restart();
    }

    function requestPreviousPage(): void {
        if (previousStepAnim.running || currentStepAnim.running || nextStepAnim.running) {
            return;
        }

        if (currentIndex === 0) {
            root.showingLanding = true;
            landingComponent.returnToLanding();
        } else {
            nextStepItemX = 0;

            currentIndex--;
            stepHeading.changeText(currentStepItem.name);

            currentStepItemX = -root.width;
            currentStepItem.visible = true;

            nextStepAnim.to = root.width;
            nextStepAnim.restart();
            currentStepAnim.to = 0;
            currentStepAnim.restart();
        }
    }

    LandingComponent {
        id: landingComponent
        anchors.fill: parent

        onRequestNextPage: {
            root.showingLanding = false;
            stepHeading.changeText(root.currentStepItem.name);
        }
    }

    PagesModel {
        id: pagesModel

        Component.onCompleted: reload()

        onLoaded: root.currentIndex = 0
    }

    Connections {
        target: pagesModel

        // onDataChanged will be emitted if the model reloads the translations
        // after the user chooses a language. We need to catch that since we are
        // using `changeText()` instead of a property binding.
        function onDataChanged(): void {
            if (root.currentIndex >= 0 && !root.showingLanding) {
                // Update the heading with the fresh translation from the model
                stepHeading.changeText(root.currentStepItem.name);
            }
        }
    }

    Item {
        id: stepsComponent
        anchors.fill: parent

        // animation when we switch to step stage
        opacity: root.showingLanding ? 0 : 1
        property real translateY: root.showingLanding ? overlaySteps.height : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.OutExpo
            }
        }

        Behavior on translateY {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.OutExpo
            }
        }

        transform: Translate {
            y: stepsComponent.translateY
        }

        // heading for all the wizard steps
        Label {
            id: stepHeading
            opacity: 0
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 18

            anchors.left: parent.left
            anchors.leftMargin: Kirigami.Units.gridUnit
            anchors.right: parent.right
            anchors.rightMargin: Kirigami.Units.gridUnit
            anchors.bottom: Kirigami.Settings.isMobile ? parent.bottom : overlaySteps.top
            anchors.bottomMargin: Kirigami.Settings.isMobile ? root.height * 0.7 + Kirigami.Units.gridUnit : Kirigami.Units.gridUnit

            property string toText

            function changeText(text: string): void {
                toText = text;
                toHidden.restart();
            }

            NumberAnimation on opacity {
                id: toHidden
                duration: 200
                to: 0
                onFinished: {
                    stepHeading.text = stepHeading.toText;
                    toShown.restart();
                }
            }

            NumberAnimation on opacity {
                id: toShown
                duration: 200
                to: 1
            }
        }

        Rectangle {
            id: overlaySteps

            Kirigami.Theme.inherit: false
            Kirigami.Theme.colorSet: Kirigami.Theme.Window

            color: Kirigami.Theme.backgroundColor
            clip: true

            radius: Kirigami.Settings.isMobile ? 0 : Kirigami.Units.cornerRadius + 2

            anchors {
                fill: Kirigami.Settings.isMobile ? parent : undefined
                topMargin: Kirigami.Settings.isMobile ? root.height * 0.3 : undefined
                centerIn: Kirigami.Settings.isMobile ? undefined : parent
            }

            width: Kirigami.Settings.isMobile ? undefined : Kirigami.Units.gridUnit * 30
            height: Kirigami.Settings.isMobile ? undefined : container.implicitHeight

            Behavior on height {
                NumberAnimation {
                    duration: Kirigami.Units.longDuration
                    easing.type: Easing.InOutQuad
                }
            }

            // all steps are in this container
            ColumnLayout {
                id: container

                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    fill: Kirigami.Settings.isMobile ? parent : undefined
                }

                Item {
                    Layout.fillWidth: true
                    Layout.minimumHeight: stepsRepeater.itemAt(root.currentIndex)?.implicitHeight ?? 0
                    Layout.fillHeight: Kirigami.Settings.isMobile

                    // setup steps
                    Repeater {
                        id: stepsRepeater
                        model: pagesModel
                        delegate: PageDelegate {}
                    }
                }

                // bottom footer
                RowLayout {
                    id: stepFooter

                    Layout.fillWidth: true

                    Button {
                        Layout.alignment: Qt.AlignLeft
                        Layout.leftMargin: Kirigami.Units.gridUnit
                        Layout.bottomMargin: Kirigami.Units.gridUnit

                        topPadding: Kirigami.Units.largeSpacing
                        bottomPadding: Kirigami.Units.largeSpacing
                        leftPadding: Kirigami.Units.gridUnit
                        rightPadding: Kirigami.Units.gridUnit

                        text: i18nc("@action:button", "Back") // qmllint disable unqualified
                        icon.name: "arrow-left-symbolic"

                        onClicked: root.requestPreviousPage()
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Button {
                        Layout.alignment: Qt.AlignRight
                        Layout.rightMargin: Kirigami.Units.gridUnit
                        Layout.bottomMargin: Kirigami.Units.gridUnit

                        topPadding: Kirigami.Units.largeSpacing
                        bottomPadding: Kirigami.Units.largeSpacing
                        leftPadding: Kirigami.Units.gridUnit
                        rightPadding: Kirigami.Units.gridUnit

                        visible: !root.onFinalPage
                        text: i18nc("@action:button", "Next") // qmllint disable unqualified
                        icon.name: "arrow-right-symbolic"

                        enabled: root.currentModule.nextEnabled

                        onClicked: root.requestNextPage()
                    }

                    Button {
                        Layout.alignment: Qt.AlignRight
                        Layout.rightMargin: Kirigami.Units.gridUnit
                        Layout.bottomMargin: Kirigami.Units.gridUnit

                        topPadding: Kirigami.Units.largeSpacing
                        bottomPadding: Kirigami.Units.largeSpacing
                        leftPadding: Kirigami.Units.gridUnit
                        rightPadding: Kirigami.Units.gridUnit

                        visible: root.onFinalPage
                        text: i18nc("@action:button", "Finish") // qmllint disable unqualified
                        icon.name: "dialog-ok-symbolic"

                        enabled: root.currentModule.nextEnabled

                        onClicked: root.finishFinalPage()
                    }
                }
            }
        }
    }

    /*!
    * Delegate that represents each page in the wizard.
    */
    component PageDelegate: Control {
        id: item

        required property int index
        required property string name

        // pass up the property
        property int currentIndex: index
        property KissComponents.SetupModule module: null

        Component.onCompleted: {
            module = pagesModel.pageItem(currentIndex);
            updateRootItems();
        }

        visible: index === 0 // the binding is broken later
        contentItem: module?.contentItem

        Binding {
            target: item.module
            property: 'cardWidth'
            value: Math.min(Kirigami.Units.gridUnit * 30, item.contentItem.width - Kirigami.Units.gridUnit * 2)
        }

        leftPadding: 0
        rightPadding: 0
        topPadding: Kirigami.Units.gridUnit

        transform: Translate {
            x: {
                if (item.currentIndex === root.currentIndex - 1) {
                    return root.previousStepItemX;
                } else if (item.currentIndex === root.currentIndex + 1) {
                    return root.nextStepItemX;
                } else if (item.currentIndex === root.currentIndex) {
                    return root.currentStepItemX;
                }
                return 0;
            }
        }

        width: parent.width

        function updateRootItems(): void {
            if (index === root.currentIndex) {
                root.currentStepItem = item;
                root.currentModule = module;
            } else if (index === root.currentIndex - 1) {
                root.previousStepItem = item;
            } else if (index === root.currentIndex + 1) {
                root.nextStepItem = item;
            }
        }

        // keep root properties updated
        Connections {
            target: root

            function onCurrentIndexChanged(): void {
                item.updateRootItems();
            }
        }
    }
}
