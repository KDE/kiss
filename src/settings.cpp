// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "initialsystemsetup.h"
#include "settings.h"

struct Settings::Private
{
	QScopedPointer<Config> cfg;
};

Settings::Settings() : d(new Private)
{
	d->cfg.reset(new Config());

	m_pages = d->cfg->stages();
	m_pages.prepend("LocalePage");
	m_pages.append("ReadyPage");
}

Settings::~Settings()
{
}

Settings *Settings::instance()
{
	Settings* inst = nullptr;
	if (inst == nullptr) {
		inst = new Settings;
	}
	return inst;
}

QString Settings::displayManager() const
{
	switch (d->cfg->displayManagerBackend()) {
	case Config::EnumDisplayManagerBackend::SDDM:
		return "sddm";
	default:
		Q_UNREACHABLE();
	}
}

QString Settings::session() const
{
	return d->cfg->desktopSession();
}

QStringList Settings::pages() const
{
	return m_pages;
}
