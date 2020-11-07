#pragma once

#include <KConfig>
#include <KConfigGroup>

#include "../Backend.h"
#include "../systemd.h"

class SDDMBackend : public Backend {
	public: SDDMBackend() {}
	public: void yeetToSession(const QString& username) override {
		KConfig conf("/etc/sddm.conf");
		auto grp = conf.group("Autologin");
		grp.writeEntry("User", username);
		grp.writeEntry("Session", "plasmawayland.desktop");
		Systemd::instance()->enableService("sddm");
		Systemd::instance()->startService("sddm");
	}
};
