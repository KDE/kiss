/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <kpackage/packagestructure.h>
#include <KLocalizedString>

class PlasmaInitialStartPackageStructure : public KPackage::PackageStructure
{
    Q_OBJECT
public:
    explicit PlasmaInitialStartPackageStructure(QObject *parent = nullptr, const QVariantList &args = QVariantList())
        : KPackage::PackageStructure(parent, args) {}
    void initPackage(KPackage::Package *package) override;
};
