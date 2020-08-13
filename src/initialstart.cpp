// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "initialstart.h"

#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <KLocalizedContext>
#include <KPackage/PackageLoader>

InitialStart::InitialStart(QObject *parent)
    : QObject(parent)
    , m_pagesModel(new PagesModel(this))
    , m_contextObj(new KLocalizedContext(this))
{
}

void InitialStart::setPagesModel(PagesModel *pagesModel)
{
    if (m_pagesModel == pagesModel) {
        return;
    }
    m_pagesModel = pagesModel;
    Q_EMIT pagesModelChanged();
}

PagesModel *InitialStart::pagesModel() const
{
    return m_pagesModel;
}

QString InitialStart::pageId() const
{
    return m_pageId;
}

void InitialStart::setPageId(const QString &pageId)
{
    if (m_pageId == pageId) {
        return;
    }
    
    m_pageId = pageId;
    m_pagePackage =  KPackage::PackageLoader::self()->loadPackage(QStringLiteral("InitialStart/Page"), pageId);
    if (!m_pagePackage.isValid()) {
        Q_EMIT pageIdChanged();
        return;
    }
}

QString InitialStart::qmlPath()
{
    if (m_pagePackage.isValid()) {
        return m_pagePackage.filePath("ui", QStringLiteral("main.qml"));
    } else {
        return QString();
    }
}

QQuickItem *InitialStart::pageItem()
{
    return createGui(m_pagePackage.filePath("ui", QStringLiteral("main.qml")));
}

QQuickItem *InitialStart::createGui(const QString &qmlPath)
{
    QQmlEngine *engine = qmlEngine(this);
    QQmlComponent *component = new QQmlComponent(engine, QUrl(qmlPath), nullptr);
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

#include "moc_initialstart.cpp"
