// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QDBusPendingCallWatcher>
#include <QObject>
#include <QStringList>

#include <KLocalizedString>

#include "systemd.h"
#include "backend.h"
#include "settings.h"
#include "displaymanagerbackends/SDDM.h"

#include <QQmlPropertyMap>
#include <optional>
#include <memory>

#include <QQuickItem>
#include "plugins/ipage.h"

static auto backends = QMap<QString,std::function<std::unique_ptr<Backend>()>> {
	{"sddm", []() -> std::unique_ptr<Backend> {return std::unique_ptr<Backend>(new SDDMBackend); } }
};

class KISS : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QQuickItem*> pages READ pages CONSTANT)

	QSharedPointer<QQmlPropertyMap> m_dataStore;
	QList<QSharedPointer<Page>> m_pages;
	QList<QQuickItem*> m_pageItems;

public:
	explicit KISS(QQmlEngine* engine, QObject *parent = nullptr);
	~KISS();

	Q_INVOKABLE void disableSelf();

	QList<QQuickItem*> pages() const;

private:
	std::unique_ptr<Backend> m_backend;
};
