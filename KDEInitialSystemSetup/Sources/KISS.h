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
#include "Backend.h"
#include "Settings.h"
#include "DisplayManagerBackends/SDDM.h"

#include <optional>

static auto backends = QMap<QString,std::function<Backend*()>> {
	{"sddm", []() -> Backend* { return new SDDMBackend; } }
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

	QVariantList m_locales;
	OrgFreedesktopAccountsInterface* m_accountsInterface;
	Backend* m_backend;
	QString m_name;

	public: KISS(QObject* parent = nullptr) : QObject(parent)
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

	public: ~KISS()
	{
		delete m_backend;
	}

	Q_PROPERTY(QVariantList locales READ locales CONSTANT)
	public: QVariantList locales() const
	{
		return m_locales;
	}

	Q_PROPERTY(QStringList pages READ pages CONSTANT)
	public: QStringList pages() const
	{
		return Settings::instance()->pages();
	}

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

	// The stuff that we may potentially use when setting stuff up
	synth_prop(QString, targetLanguage, QStringLiteral("en_US"))

	synth_prop(QString, username, QString())
	synth_prop(QString, realname, QString())
	synth_prop(QString, password, QString())
	synth_prop(bool, admin, true)

	public: Q_INVOKABLE void disableSelf()
	{
		auto reply = m_accountsInterface->CreateUser(username(), realname(), admin() ? 1 : 0);
		auto user = OrgFreedesktopAccountsUserInterface(QStringLiteral("org.freedesktop.Accounts"), reply.value().path(), QDBusConnection::systemBus(), this);
		user.SetLanguage(targetLanguage());
		user.SetPassword(password(), QString());

		Systemd::instance()->disableService("org.kde.initialsystemsetup");

		m_backend->yeetToSession(username());

		Systemd::instance()->stopService("org.kde.initialsystemsetup");
	}
};
