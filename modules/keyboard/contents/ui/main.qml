// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kitemmodels as KItemModels
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.initialsystemsetup.components as KissComponents
import org.kde.initialsystemsetup.keyboard as Keyboard

import org.kde.plasma.private.kcm_keyboard as KCMKeyboard

KissComponents.SetupModule {
    id: root

    nextEnabled: true

    KItemModels.KSortFilterProxyModel {
        id: keyboardsProxy
        sourceModel: KCMKeyboard.KeyboardModel {}
        sortRoleName: "description"
        sortOrder: Qt.AscendingOrder
    }

    contentItem: KCMKeyboard.LayoutSelector {}

    // contentItem: ScrollView {
    // Component.onCompleted: {
    // if (background) {
    // background.visible = true
    // }
    // }

    // contentItem: ListView {
    // id: layoutsView
    // currentIndex: 0
    // model: KCMKeyboard.LayoutModel {}
    // delegate: LayoutDelegate {}
    // keyNavigationEnabled: true
    // activeFocusOnTab: true

    // onCurrentItemChanged: variantProxy.invalidateFilter()
    // }
    // }

    component LayoutDelegate: ItemDelegate {
        id: delegate

        width: ListView.view.width
        highlighted: ListView.isCurrentItem

        required property string shortName
        required property string description
        required property string variantName
        required property int index

        onClicked: ListView.view.currentIndex = index

        Accessible.name: delegate.description

        contentItem: Kirigami.IconTitleSubtitle {
            icon.source: KCMKeyboard.Flags.getIcon(delegate.shortName)
            title: delegate.description

            ToolTip.text: title
            ToolTip.visible: delegate.hovered && truncated
        }
    }
}
