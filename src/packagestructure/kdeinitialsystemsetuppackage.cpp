// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "kdeinitialsystemsetuppackage.h"

#include <KPackage/Package>

void KDEInitialSystemSetupPackageStructure::initPackage(KPackage::Package *package)
{
    package->setDefaultPackageRoot(QStringLiteral("plasma/packages"));
    package->addDirectoryDefinition("ui", QStringLiteral("ui"));

    package->addFileDefinition("mainscript", QStringLiteral("ui/main.qml"));
    package->setRequired("mainscript", true);
}

K_PLUGIN_CLASS_WITH_JSON(KDEInitialSystemSetupPackageStructure, "kde-initialsystemsetup-packagestructure.json")

#include "kdeinitialsystemsetuppackage.moc"

#include "moc_kdeinitialsystemsetuppackage.cpp"
