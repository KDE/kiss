/*
SPDX-FileCopyrightText: 2024 Evgeny Chesnokov <echesnokov@astralinux.ru>
SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*/

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.kitemmodels as KItemModels

import org.kde.initialsystemsetup
import org.kde.initialsystemsetup.components as KissComponents
import org.kde.initialsystemsetup.keyboard as Keyboard

import org.kde.plasma.private.kcm_keyboard as KCMKeyboard

KissComponents.SetupModule {
    id: root

    cardWidth: Math.min(Kirigami.Units.gridUnit * 30, root.contentItem.width - Kirigami.Units.gridUnit * 2)
    nextEnabled: true

    KCMKeyboard.LayoutSearchModel {
        id: layoutSearchProxy
        sourceModel: KCMKeyboard.LayoutModel {}
        searchString: ""
    }

    KItemModels.KSortFilterProxyModel {
        id: layoutsProxy
        sourceModel: layoutSearchProxy
        sortRoleName: "searchScore"
        sortOrder: Qt.AscendingOrder

        filterRowCallback: function (row, parent) {
            const modelIndex = sourceModel.index(row, 0, parent);
            const currentVariantName = sourceModel.data(modelIndex, KItemModels.KRoleNames.role("variantName"));
            const description = sourceModel.data(modelIndex, KItemModels.KRoleNames.role("description"));

            if (currentVariantName !== '') {
                return false;
            }

            if (searchField.text.length > 0) {
                const score = sourceModel.data(modelIndex, KItemModels.KRoleNames.role("searchScore"));
                if (score !== 0) {
                    return true;
                }
                const shortNameRole = KItemModels.KRoleNames.role("shortName");
                const currentName = sourceModel.data(modelIndex, shortNameRole);
                const searchScoreRole = KItemModels.KRoleNames.role("searchScore");
                for (let i = 0; i < sourceModel.rowCount(); i++) {
                    const index = sourceModel.index(i, 0, parent);
                    const name = sourceModel.data(index, shortNameRole);
                    const variantSearchScore = sourceModel.data(index, searchScoreRole);
                    if (name === currentName && variantSearchScore > 100) {
                        return true;
                    }
                }
                return false;
            }

            return true;
        }
    }

    KItemModels.KSortFilterProxyModel {
        id: variantProxy
        sourceModel: layoutSearchProxy
        sortRoleName: "searchScore"
        sortOrder: Qt.AscendingOrder

        filterRowCallback: function (row, parent) {
            if (!layoutsView.currentItem) {
                return false;
            }

            const modelIndex = sourceModel.index(row, 0, parent);
            const currentName = sourceModel.data(modelIndex, KItemModels.KRoleNames.role("shortName"));
            const selectedName = layoutsView.currentItem.shortName;

            if (currentName !== selectedName) {
                return false;
            }

            if (searchField.text.length > 0) {
                const searchScore = sourceModel.data(modelIndex, KItemModels.KRoleNames.role("searchScore"));
                return searchScore > 100;
            }

            return true;
        }
    }

    contentItem: ScrollView {
        id: mainScrollView
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentWidth: -1

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.gridUnit

            Label {
                Layout.leftMargin: Kirigami.Units.gridUnit
                Layout.rightMargin: Kirigami.Units.gridUnit
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                text: i18n("Select your keyboard layout and language.") // qmllint disable unqualified
            }

            FormCard.FormCard {
                id: keyboardLayoutCard
                maximumWidth: root.cardWidth

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                Layout.fillWidth: true

                FormCard.AbstractFormDelegate {
                    background: null
                    Layout.fillWidth: true

                    contentItem: ColumnLayout {
                        spacing: Kirigami.Units.smallSpacing
                        width: parent.width

                        Kirigami.SearchField {
                            id: searchField
                            Layout.fillWidth: true
                            onAccepted: {
                                layoutSearchProxy.searchString = searchField.text.trim();
                            }
                        }

                        RowLayout {
                            ScrollView {
                                clip: true
                                implicitWidth: Math.round(mainScrollView.width / 2)
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.maximumHeight: Kirigami.Units.gridUnit * 14

                                Component.onCompleted: {
                                    if (background) {
                                        background.visible = true;
                                    }
                                }

                                contentItem: ListView {
                                    id: layoutsView
                                    currentIndex: 0
                                    model: layoutsProxy
                                    delegate: LayoutDelegate {}
                                    keyNavigationEnabled: true
                                    activeFocusOnTab: true

                                    onCurrentItemChanged: variantProxy.invalidateFilter()
                                }
                            }

                            ScrollView {
                                clip: true
                                implicitWidth: Math.round(mainScrollView.width / 2)
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.maximumHeight: Kirigami.Units.gridUnit * 14

                                Component.onCompleted: {
                                    if (background) {
                                        background.visible = true;
                                    }
                                }

                                contentItem: ListView {
                                    id: variantView
                                    model: layoutsView.currentItem ? variantProxy : []
                                    delegate: LayoutDelegate {}
                                    keyNavigationEnabled: true
                                    activeFocusOnTab: true
                                }
                            }
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    component LayoutDelegate: ItemDelegate {
        id: delegate

        width: ListView.view.width
        highlighted: ListView.isCurrentItem

        required property string shortName
        required property string description
        required property string variantName
        required property int index

        onClicked: {
            ListView.view.currentIndex = index;
            KeyboardUtil.setLayout(shortName, variantName);
        }

        Accessible.name: delegate.description

        contentItem: Kirigami.IconTitleSubtitle {
            icon.source: KCMKeyboard.Flags.getIcon(delegate.shortName)
            title: delegate.description

            ToolTip.text: title
            ToolTip.visible: delegate.hovered && truncated
        }
    }
}
