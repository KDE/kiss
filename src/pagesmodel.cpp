// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "pagesmodel.h"
#include "initialstartmodule.h"

#include <QDebug>

#include <KLocalizedString>
#include <KPackage/PackageLoader>
#include <KPluginMetaData>

using namespace Qt::StringLiterals;

PagesModel::PagesModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

void PagesModel::reload()
{
    clear();

    auto packages = KPackage::PackageLoader::self()->listKPackages(QStringLiteral("KDE/InitialSystemSetup"));

    std::ranges::sort(packages, [](const KPackage::Package &left, const KPackage::Package &right) {
        const auto leftData = left.metadata().rawData();
        const auto rightData = right.metadata().rawData();
        return leftData["X-KDE-Weight"_L1].toInt() < rightData["X-KDE-Weight"_L1].toInt();
    });

    for (const auto &package : std::as_const(packages)) {
        const auto plugin = package.metadata();
        auto item = new QStandardItem(plugin.name());
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

SetupModule *PagesModel::pageItem(int row)
{
    const auto package = data(index(row, 0), PackageRole).value<KPackage::Package>();
    return createGui(package.filePath("ui", QStringLiteral("main.qml")));
}

SetupModule *PagesModel::createGui(const QString &qmlPath)
{
    QQmlEngine *engine = qmlEngine(this);
    auto component = new QQmlComponent(engine, QUrl(qmlPath), nullptr);
    QObject *guiObject = component->create();

    if (component->status() != QQmlComponent::Ready) {
        qCritical() << "Error creating component:" << component->errors();
        component->deleteLater();
        return nullptr;
    }

    auto module = qobject_cast<SetupModule *>(guiObject);

    if (!module) {
        qWarning() << "ERROR: QML gui" << guiObject << "not a QQuickItem instance" << qmlPath;
        guiObject->deleteLater();
        return nullptr;
    }
    module->setParent(this);
    return module;
}

#include "moc_pagesmodel.cpp"
