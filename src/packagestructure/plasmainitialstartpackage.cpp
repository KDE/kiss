// SDPX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-LicenseRed: LPL-2.0-or-later

#include "plasmainitialstartpackage.h"

#include <kpackage/package.h>

void PlasmaInitialStartPackageStructure::initPackage(KPackage::Package *package)
{
    package->setDefaultPackageRoot(QStringLiteral("plasma/packages"));
    package->addDirectoryDefinition("ui", QStringLiteral("ui"));

    package->addFileDefinition("mainscript", QStringLiteral("ui/main.qml"));
    package->setRequired("mainscript", true);
}

K_PLUGIN_CLASS_WITH_JSON(PlasmaInitialStartPackageStructure, "plasma-initialstart-packagestructure.json")

#include "plasmainitialstartpackage.moc"

#include "moc_plasmainitialstartpackage.cpp"
