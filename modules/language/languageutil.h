// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QQmlEngine>

/**
 * @brief Handles language choice.
 *
 * This class provides functionality to load available languages,
 * set the current language, and apply the selected language.
 *
 * Language choice applies to this application, as well as either the live session or
 * the newly created user depending on the context of how we are running.
 */
class LanguageUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    /**
     * @brief List of available languages in the system.
     *
     * A list of language codes that are available for use in the application.
     * Each entry in the list represents a language that can be selected by the user.
     */
    Q_PROPERTY(QStringList availableLanguages READ availableLanguages NOTIFY availableLanguagesChanged)

    /**
     * @brief The language code of the currently selected language.
     */
    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setCurrentLanguage NOTIFY currentLanguageChanged)

public:
    explicit LanguageUtil(QObject *parent = nullptr);

    QStringList availableLanguages() const;
    QString currentLanguage() const;
    void setCurrentLanguage(const QString &language);

    /**
     * @brief Applies the chosen language to the application and system settings.
     */
    Q_INVOKABLE void applyLanguage();

Q_SIGNALS:
    void availableLanguagesChanged();
    void currentLanguageChanged();

private:
    /**
     * @brief Loads the available languages from the system.
     *
     * This function populates the availableLanguages list with the languages
     * that are supported by Plasma.
     */
    void loadAvailableLanguages();

    QStringList m_availableLanguages;
    QString m_currentLanguage;
};
