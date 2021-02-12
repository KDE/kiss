// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "settings.h"

Settings::Settings()
{
	m_settings = g_settings_new("org.kde.initialsystemsetup");

	GVariantIter *iter;
	gchar *str;

	m_pages << "LocalePage";
	g_settings_get(m_settings, "stages", "as", &iter);
	while (g_variant_iter_loop (iter, "s", &str))
		m_pages << QString::fromLocal8Bit(str);
	m_pages << "ReadyPage";

	g_variant_iter_free(iter);

	auto session = g_settings_get_string(m_settings, "desktop-session");
	m_session = QString::fromLocal8Bit(session);
	g_free(session);

	auto dm = g_settings_get_string(m_settings, "display-manager-backend");
	m_dm = QString::fromLocal8Bit(dm);
	g_free(dm);
}

Settings::~Settings()
{
	g_free(m_settings);
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
	return m_dm;
}

QString Settings::session() const
{
	return m_session;
}

QStringList Settings::pages() const
{
	return m_pages;
}
