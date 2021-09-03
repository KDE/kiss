// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QDBusPendingCallWatcher>
#include <QObject>
#include <QStringList>

#include <KLocalizedString>

#include "AccountsService.h"
#define org org_collision_prevention
#include "User.h"
#undef org

#include "systemd.h"
#include "backend.h"
#include "settings.h"
#include "displaymanagerbackends/SDDM.h"

#include <crack.h>

#include <optional>
#include <memory>

static auto backends = QMap<QString,std::function<std::unique_ptr<Backend>()>> {
	{"sddm", []() -> std::unique_ptr<Backend> {return std::unique_ptr<Backend>(new SDDMBackend); } }
};

struct Language
{
	Q_GADGET

public:
	Q_PROPERTY(QString name MEMBER m_name CONSTANT)
	QString m_name;

	Q_PROPERTY(QString code MEMBER m_code CONSTANT)
	QString m_code;
};

class KISS : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList locales READ locales CONSTANT)
	Q_PROPERTY(QStringList pages READ pages CONSTANT)

#define synth_prop(kind, name, default) Q_PROPERTY(kind name READ name WRITE set_ ## name RESET reset_ ## name NOTIFY name ## _changed) \
std::optional<kind> m_ ## name;\
Q_SIGNAL void name ## _changed();\
public: kind name() {\
	return m_ ## name.value_or(default);\
}\
public: void set_ ## name(const kind& t) {\
	if (!m_ ## name.has_value() || m_ ## name.value() != t) {\
		m_ ## name = t; Q_EMIT name ## _changed();\
	}\
}\
public: void reset_ ## name() {\
	if (m_ ## name.has_value()) {\
		m_ ## name.reset(); Q_EMIT name ## _changed();\
	}\
}
	synth_prop(QString, targetLanguage, QStringLiteral("en_US"))

	synth_prop(QString, username, QString())
	synth_prop(QString, realname, QString())
	synth_prop(QString, password, QString())
	synth_prop(bool, admin, true)

public:
	explicit KISS(QObject *parent = nullptr);
	~KISS();

	Q_INVOKABLE void disableSelf();
	Q_INVOKABLE QString checkPassword(const QString& username, const QString& realname, const QString& password);

	QVariantList locales() const;
	QStringList pages() const;

private:
	QVariantList m_locales;
	OrgFreedesktopAccountsInterface* m_accountsInterface;
	std::unique_ptr<Backend> m_backend;
};
