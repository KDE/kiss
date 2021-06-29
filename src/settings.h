// SPDX-FileCopyrightText: 2021 Carson Black <> // TODO
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QString>
#include <QStringList>
#include <QScopedPointer>

/// Settings for KISS
class Settings
{
private:
	Settings();
	~Settings();

	struct Private;
	QScopedPointer<Private> d;

public:
	static Settings *instance();
	QString displayManager() const;
	QString session() const;
	QStringList pages() const;

private:
	QStringList m_pages;

};
