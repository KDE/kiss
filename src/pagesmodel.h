// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#pragma once

#include "initialstartmodule.h"
#include <KLocalizedContext>
#include <QQuickItem>
#include <QStandardItemModel>
#include <qqmlregistration.h>

class PagesModel : public QStandardItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum AdditionalRoles {
        PluginIdRole = Qt::UserRole + 1,
        PackageRole,
    };
    Q_ENUM(AdditionalRoles)

    PagesModel(QObject *parent = nullptr);
    ~PagesModel() = default;

    Q_INVOKABLE void reload();
    Q_INVOKABLE QString pluginId(int row);

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE SetupModule *pageItem(int row);

Q_SIGNALS:
    void loaded();

private:
    SetupModule *createGui(const QString &qmlPath);
};