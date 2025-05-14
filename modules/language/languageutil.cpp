// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <KLocalizedString>

#include "languageutil.h"

LanguageUtil::LanguageUtil(QObject *parent)
    : QObject(parent)
{
    loadAvailableLanguages();
    m_currentLanguage = QLocale::system().name();
}

QStringList LanguageUtil::availableLanguages() const
{
    return m_availableLanguages;
}

QString LanguageUtil::currentLanguage() const
{
    return m_currentLanguage;
}

void LanguageUtil::setCurrentLanguage(const QString &language)
{
    if (m_currentLanguage != language) {
        m_currentLanguage = language;
        Q_EMIT currentLanguageChanged();
    }
}

void LanguageUtil::applyLanguage()
{
    if (m_currentLanguage.isEmpty()) {
        return;
    }

    qDebug() << "Applying language:" << m_currentLanguage;

    // TODO: Apply the language to the system settings for the new user.

    qDebug() << "Language settings applied successfully";
}

void LanguageUtil::loadAvailableLanguages()
{
    m_availableLanguages = KLocalizedString::availableDomainTranslations("plasmashell").values();

    // Ensure we at least have English available
    if (!m_availableLanguages.contains(QStringLiteral("en_US"))) {
        m_availableLanguages.append(QStringLiteral("en_US"));
    }

    m_availableLanguages.sort();

    Q_EMIT availableLanguagesChanged();
}
