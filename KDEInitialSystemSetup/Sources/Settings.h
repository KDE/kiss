// SPDX-FileCopyrightText: 2021 Carson Black <> // TODO
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef signals
#include <gio/gio.h>
#include <QString>
#include <QStringList>

/// Settings for KISS
class Settings
{
private:
	Settings();
	~Settings();

public:
	static Settings *instance();
	QString displayManager() const;
	QString session() const;
	QStringList pages() const;

private:
	GSettings* m_settings;
	QStringList m_pages;
	QString m_dm;
	QString m_session;
};
