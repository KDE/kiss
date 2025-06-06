// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.initialsystemsetup.language as Language

import org.kde.initialsystemsetup.components as KissComponents

/**
* @brief Module for selecting system language
*
* This module provides a user interface for selecting the system language.
* It displays a scrollable list of available languages with search functionality
* to help users easily find and select their preferred language.
*/
KissComponents.SetupModule {
    id: root

    cardWidth: Math.min(Kirigami.Units.gridUnit * 30, root.contentItem.width - Kirigami.Units.gridUnit * 2)
    nextEnabled: true

    contentItem: ScrollView {
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
                text: i18n("Please select your preferred language.") // qmllint disable unqualified
            }

            FormCard.FormCard {
                id: languageCard
                maximumWidth: root.cardWidth

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                Layout.fillWidth: true

                FormCard.AbstractFormDelegate {
                    background: null
                    Layout.fillWidth: true

                    contentItem: ColumnLayout {
                        spacing: Kirigami.Units.smallSpacing
                        width: parent.width

                        Label {
                            Layout.fillWidth: true
                            text: i18n("Language") // qmllint disable unqualified
                            wrapMode: Text.Wrap
                            elide: Text.ElideRight
                            horizontalAlignment: Text.AlignLeft
                            font.bold: true
                        }

                        Control {
                            Layout.fillWidth: true

                            leftPadding: Kirigami.Units.largeSpacing
                            rightPadding: Kirigami.Units.largeSpacing
                            topPadding: Kirigami.Units.largeSpacing
                            bottomPadding: Kirigami.Units.largeSpacing

                            contentItem: Kirigami.SearchField {
                                id: searchField
                                placeholderText: i18n("Search languages...") // qmllint disable unqualified
                                property string filterString: ""

                                onTextChanged: {
                                    filterString = text.toLowerCase();
                                }
                            }
                        }

                        Kirigami.Separator {
                            Layout.fillWidth: true
                        }

                        ScrollView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.minimumHeight: Kirigami.Units.gridUnit * 14
                            Layout.maximumHeight: Kirigami.Units.gridUnit * 14

                            ListView {
                                id: languageListView
                                clip: true
                                model: Language.LanguageUtil.availableLanguages

                                // Filter languages based on search text
                                function matchesFilter(language) {
                                    if (!searchField.filterString) {
                                        return true;
                                    }

                                    // Get language name from locale code
                                    const localeName = Qt.locale(language).nativeLanguageName;
                                    return language.toLowerCase().includes(searchField.filterString) || localeName.toLowerCase().includes(searchField.filterString);
                                }

                                currentIndex: -1 // Ensure focus is not on the listview
                                bottomMargin: 2

                                delegate: FormCard.FormRadioDelegate {
                                    required property string modelData

                                    // Show and hide based on filter
                                    readonly property bool matchesFilter: languageListView.matchesFilter(modelData)
                                    height: matchesFilter ? implicitHeight : 0
                                    visible: matchesFilter

                                    width: ListView.view.width

                                    // Get language name from locale code (e.g., "en_US" -> "English (United States)")
                                    text: {
                                        const locale = Qt.locale(modelData);
                                        const localeName = locale.nativeLanguageName;
                                        // First letter to uppercase
                                        return localeName.charAt(0).toUpperCase() + localeName.slice(1) + " (" + locale.nativeCountryName + ")";
                                    }

                                    checked: Language.LanguageUtil.currentLanguage === modelData

                                    onToggled: {
                                        if (checked && modelData !== Language.LanguageUtil.currentLanguage) {
                                            Language.LanguageUtil.currentLanguage = modelData;
                                            Language.LanguageUtil.applyLanguage();
                                            checked = Qt.binding(() => Language.LanguageUtil.currentLanguage === modelData);
                                        }
                                    }
                                }

                                function scrollToCurrentLanguage() {
                                    // Find the index of the current language
                                    const currentLang = Language.LanguageUtil.currentLanguage;
                                    for (let i = 0; i < model.length; i++) {
                                        if (model[i] === currentLang) {
                                            // Position the view at the current language with some offset
                                            positionViewAtIndex(i, ListView.Center);
                                            break;
                                        }
                                    }
                                }

                                Component.onCompleted: {
                                    // Scroll to the current language when the view is ready
                                    if (Language.LanguageUtil.currentLanguage) {
                                        scrollToCurrentLanguage();
                                    }
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
}
