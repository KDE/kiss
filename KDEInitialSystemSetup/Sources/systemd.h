#pragma once

#include <QDBusConnection>
#include <QDBusInterface>

class Systemd
{
	QDBusInterface* m_daemon;

	public: Systemd()
	{
		m_daemon = new QDBusInterface("org.freedesktop.systemd1", "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager", QDBusConnection::systemBus());
	}
	public: ~Systemd()
	{
		delete m_daemon;
	}
	private: QString s(const QString& unit)
	{
		return unit + ".service";
	}
	private: void checkCall(QDBusMessage msg)
	{
		if (msg.type() == QDBusMessage::ErrorMessage) {
			qWarning() << "dbus call failed (" << msg.errorName() << "):" << msg.errorMessage();
		}
	}
	public: void enableService(const QString& name)
	{
		checkCall(m_daemon->call("EnableUnitFiles", QStringList{s(name)}, false, true));
	}
	public: void disableService(const QString& name)
	{
		checkCall(m_daemon->call("DisableUnitFiles", QStringList{s(name)}, false));
	}
	public: void startService(const QString& name)
	{
		checkCall(m_daemon->call("StartUnit", s(name), "replace"));
	}
	public: void stopService(const QString& name)
	{
		checkCall(m_daemon->call("StopUnit", s(name), "replace"));
	}
};
