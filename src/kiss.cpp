// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "kiss.h"

KISS::KISS(QObject* parent)
	: QObject(parent)
{
	m_backend = backends[Settings::instance()->displayManager()]();

	auto locs = KLocalizedString::availableDomainTranslations("plasmashell").values();
	std::transform(locs.begin(), locs.end(), std::back_inserter(m_locales), [](const QString& locale) -> QVariant {
		return QVariant::fromValue(Language {
			.m_name = QLocale(locale).nativeLanguageName(),
			.m_code = locale
		});
	});
	std::sort(m_locales.begin(), m_locales.end(), [](const QVariant& lhs, const QVariant& rhs) -> bool {
		return lhs.value<Language>().m_name < rhs.value<Language>().m_name;
	});
	m_accountsInterface = new OrgFreedesktopAccountsInterface(QStringLiteral("org.freedesktop.Accounts"), QStringLiteral("/org/freedesktop/Accounts"), QDBusConnection::systemBus(), this);
}

KISS::~KISS()
{}

QVariantList KISS::locales() const
{
	return m_locales;
}

QStringList KISS::pages() const
{
	return Settings::instance()->pages();
}

void KISS::disableSelf()
{
	auto reply = m_accountsInterface->CreateUser(username(), realname(), admin() ? 1 : 0);
	auto user = OrgFreedesktopAccountsUserInterface(QStringLiteral("org.freedesktop.Accounts"), reply.value().path(), QDBusConnection::systemBus(), this);
	user.SetLanguage(targetLanguage());
	user.SetPassword(password(), QString());

	Systemd::instance()->disableService("org.kde.initialsystemsetup");

	m_backend->yeetToSession(username());

	Systemd::instance()->stopService("org.kde.initialsystemsetup");
}

QString KISS::checkPassword(const QString& username, const QString& realname, const QString& password)
{
	auto usernameData = username.toLocal8Bit();
	auto realnameData = realname.toLocal8Bit();
	auto passwordData = password.toLocal8Bit();

	usernameData.data();

	auto data = FascistCheckUser(passwordData.data(), GetDefaultCracklibDict(), usernameData.data(), realnameData.data());
	if (data == nullptr) {
		return QString();
	}
	return QString::fromLocal8Bit(data);
}
