// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "languageutil.h"

#include <KLocalizedString>

#include <QCoreApplication>

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

    applyLanguageForCurrentSession();

    Q_EMIT currentLanguageChanged();
}

bool LanguageUtil::applyLanguageForCurrentSession()
{
    qputenv("LANGUAGE", m_currentLanguage.toUtf8());
    qputenv("LANG", m_currentLanguage.toUtf8());
    QLocale::setDefault(QLocale(m_currentLanguage));

    QEvent localeChangeEvent(QEvent::LocaleChange);
    QCoreApplication::sendEvent(QCoreApplication::instance(), &localeChangeEvent);
    QEvent languageChangeEvent(QEvent::LanguageChange);
    QCoreApplication::sendEvent(QCoreApplication::instance(), &languageChangeEvent);

    return true;
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
