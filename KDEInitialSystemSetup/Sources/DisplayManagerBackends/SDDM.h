#pragma once

#include <KConfig>
#include <KConfigGroup>

#include "../Backend.h"
#include "../systemd.h"
#include "../Settings.h"

class SDDMBackend : public Backend {
	public: SDDMBackend() {}
	public: void yeetToSession(const QString& username) override {
		KConfig conf("/etc/sddm.conf");
		auto grp = conf.group("Autologin");

		grp.writeEntry("User", username);
		grp.writeEntry("Session", Settings::instance()->session());

		Systemd::instance()->enableService("sddm");
		Systemd::instance()->startService("sddm");
	}
};
