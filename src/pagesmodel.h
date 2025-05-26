// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#pragma once

#include <QQuickItem>
#include <QStandardItemModel>

#include "setupmodule.h"

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
    /**
     * Listening for language changes so we can trigger a reload of the translations.
     *
     * The language module will emit the language change event when it changes the language.
     *
     * This is primarily needed because we fetch the module name from the package metadata,
     * and we have the translations from the previous language cached.
     */
    bool eventFilter(QObject *object, QEvent *event) override;

    /**
     * Updates translations for all items in the model when the language changes.
     *
     * This way we avoid reloading the entire model when only the translations need to be updated.
     */
    void updateTranslations();

    SetupModule *createGui(const QString &qmlPath);
};
