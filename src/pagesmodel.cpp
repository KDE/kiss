// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "pagesmodel.h"

#include <QDebug>

#include <KPackage/PackageLoader>
#include <KLocalizedString>
#include <KPluginMetaData>

PagesModel::PagesModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

void PagesModel::reload()
{
    clear();

    const auto packages = KPackage::PackageLoader::self()->listKPackages(QStringLiteral("Plasma/InitialStart"));

    for (const auto &package : packages) {
        const auto plugin = package.metadata();
        auto item = new QStandardItem(plugin.name());
        qWarning() << plugin.name();
        item->setData(plugin.pluginId(), PagesModel::PluginIdRole);
        item->setData(QVariant::fromValue(package), PagesModel::PackageRole);
        appendRow(item);
    }

    Q_EMIT loaded();
}

QString PagesModel::pluginId(int row)
{
    return data(index(row, 0), PluginIdRole).toString();
}

QHash<int, QByteArray> PagesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
 
    roles[PluginIdRole] = "pluginId";
    roles[Qt::DisplayRole] = "name";
    return roles;
}

QQuickItem *PagesModel::pageItem(int row)
{
    const auto package = data(index(row, 0), PackageRole).value<KPackage::Package>();
    return createGui(package.filePath("ui", QStringLiteral("main.qml")));
}

QQuickItem *PagesModel::createGui(const QString &qmlPath)
{
    QQmlEngine *engine = qmlEngine(this);
    auto component = new QQmlComponent(engine, QUrl(qmlPath), nullptr);
    if (component->status() != QQmlComponent::Ready) {
        qCritical() << "Error creating component:";
        const auto errors = component->errors();
        for (const auto &err : errors) {
            qWarning() << err.toString();
        }
        component->deleteLater();
        return nullptr;
    }

    QObject *guiObject = component->create();
    QQuickItem *gui = qobject_cast<QQuickItem *>(guiObject);
    if (!gui) {
        qWarning() << "ERROR: QML gui" << guiObject << "not a QQuickItem instance";
        guiObject->deleteLater();
        return nullptr;
    }
    gui->setParent(this);
    return gui;
}

#include "moc_pagesmodel.cpp"
