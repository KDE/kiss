#include <QCoreApplication>
#include <QQmlComponent>
#include <QQuickItem>

#include "ipage.h"

Page::Page(QObject* parent)
{

}

Page::~Page()
{

}

QQuickItem* createItemFromURL(const QString& uri, QQmlEngine* eng, QObject* ctxt)
{
    QQmlComponent* comp = new QQmlComponent(eng, uri, ctxt);

    while (comp->status() == QQmlComponent::Loading)
    {
        QCoreApplication::processEvents();
    }

    if (comp->status() != QQmlComponent::Ready)
    {
        qFatal("component failed to load");
    }

    auto obj = comp->createWithInitialProperties({{"page", QVariant::fromValue(ctxt)}});
    auto item = qobject_cast<QQuickItem*>(obj);
    if (item == nullptr)
    {
        qFatal("component isn't qquickitem");
    }

    return item;
}
