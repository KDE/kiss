// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QQmlEngine>

/**
 * Handles language choice.
 *
 * This class provides functionality to load available languages,
 * set the current language, and apply the selected language.
 *
 * Language choice applies to this application, as well as the session if we are
 * running in a live environment. When setting the language for a newly created
 * user, reference the result of QLocale::system() for chosen language.
 */
class LanguageUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    /**
     * List of available languages in the system.
     *
     * A list of language codes that are available for use in the application.
     * Each entry in the list represents a language that can be selected by the user.
     */
    Q_PROPERTY(QStringList availableLanguages READ availableLanguages NOTIFY availableLanguagesChanged)

    /**
     * The language code of the currently selected language.
     */
    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setCurrentLanguage NOTIFY currentLanguageChanged)

public:
    explicit LanguageUtil(QObject *parent = nullptr);

    QStringList availableLanguages() const;
    QString currentLanguage() const;
    void setCurrentLanguage(const QString &language);

    /**
     * Applies the chosen language to the running application.
     */
    Q_INVOKABLE void applyLanguage();

Q_SIGNALS:
    void availableLanguagesChanged();
    void currentLanguageChanged();

private:
    /**
     * Loads the available languages from the system.
     *
     * This function populates the availableLanguages list with the languages
     * that are supported by Plasma.
     */
    void loadAvailableLanguages();

    QStringList m_availableLanguages;
    QString m_currentLanguage;
};
