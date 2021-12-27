// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pages/localepage.h"
#include "pages/readypage.h"
#include "plugins/pageloader.h"
#include "kiss.h"

KISS::KISS(QQmlEngine* engine, QObject* parent)
	: QObject(parent)
{
	m_backend = backends[Settings::instance()->displayManager()]();

	m_dataStore.reset(new QQmlPropertyMap(this));

	m_pages = { QSharedPointer<Page>(new LocalePage(m_dataStore.data(), this)) };

	for (const auto& page : Settings::instance()->pages())
	{
		auto pg = loadPage("page_" + page, m_dataStore.data());
		if (!pg) {
			qFatal("failed to find page %s", page.toUtf8().data());
		}
		m_pages << pg;
	}

	m_pages << QSharedPointer<Page>(new ReadyPage(m_dataStore.data(), this));

	for (auto& page : m_pages) {
		m_pageItems << page->createItem(engine);
	}
}

KISS::~KISS()
{}

QList<QQuickItem*> KISS::pages() const
{
	return m_pageItems;
}

void KISS::disableSelf()
{
	Systemd::instance()->disableService("org.kde.initialsystemsetup");

	for (const auto& page : m_pages) {
		// TODO: refactor to use coroutine integration
		page->apply();
	}

	Systemd::instance()->stopService("org.kde.initialsystemsetup");
}
