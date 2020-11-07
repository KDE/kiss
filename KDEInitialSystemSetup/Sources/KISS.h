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
#include "DisplayManagerBackends/SDDM.h"

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
		m_backend = new SDDMBackend;
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

	Q_PROPERTY(QVariantList locales READ locales)
	public: QVariantList locales() const
	{
		return m_locales;
	}

	public: Q_SIGNAL void finished(bool success);
	public: Q_INVOKABLE void createAccount(const QString& realname, const QString& username, const QString& password, const bool& admin, const QString& language)
	{
		auto watcher = new QDBusPendingCallWatcher(m_accountsInterface->CreateUser(username, realname, admin ? 1 : 0), this);
		connect(watcher, &QDBusPendingCallWatcher::finished, [=, this](QDBusPendingCallWatcher* self) {
			QDBusPendingReply<QDBusObjectPath> reply = *self;

			if (reply.isError()) {
				Q_EMIT finished(false);
				return;
			}

			auto user = OrgFreedesktopAccountsUserInterface(QStringLiteral("org.freedesktop.Accounts"), reply.value().path(), QDBusConnection::systemBus(), this);
			m_name = user.userName();
			user.SetLanguage(language);
			user.SetPassword(password, QString());

			Q_EMIT finished(true);
		});
	}

	public: Q_INVOKABLE void disableSelf()
	{
		Systemd::instance()->disableService("org.kde.initialsystemsetup");

		m_backend->yeetToSession(m_name);

		Systemd::instance()->stopService("org.kde.initialsystemsetup");
	}
};
