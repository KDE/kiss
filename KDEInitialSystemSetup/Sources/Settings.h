#pragma once

#undef signals
#include <gio/gio.h>

class Settings
{
	GSettings* m_settings;
	QStringList m_pages;
	QString m_dm;
	QString m_session;

	private: Settings()
	{
		m_settings = g_settings_new("org.kde.initialsystemsetup");

		GVariantIter *iter;
		gchar *str;

		m_pages << "locale";
		g_settings_get(m_settings, "stages", "as", &iter);
		while (g_variant_iter_loop (iter, "s", &str))
			m_pages << QString::fromLocal8Bit(str);
		m_pages << "ready";

		g_variant_iter_free (iter);

		auto session = g_settings_get_string(m_settings, "desktop-session");
		m_session = QString::fromLocal8Bit(session);
		g_free(session);

		auto dm = g_settings_get_string(m_settings, "display-manager-backend");
		m_dm = QString::fromLocal8Bit(dm);
		g_free(dm);
	}
	private: ~Settings()
	{
		g_free(m_settings);
	}
	public: static Settings* instance()
	{
		Settings* inst = nullptr;
		if (inst == nullptr) {
			inst = new Settings;
		}
		return inst;
	}
	public: QString displayManager() const
	{
		return m_dm;
	}
	public: QString session() const
	{
		return m_session;
	}
	public: QStringList pages() const
	{
		return m_pages;
	}
};
