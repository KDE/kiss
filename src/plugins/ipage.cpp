#include <QCoreApplication>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQmlPropertyMap>

#include "ipage.h"

Page::Page(QObject* parent, const KPluginMetaData&, const QVariantList& args)
{
    if (args.length() < 1)
        qFatal("invalid args length. expected at least 1, got %d", args.length());

    m_dataStore = qvariant_cast<QQmlPropertyMap*>(args[0]);
    if (!m_dataStore) {
        qFatal("invalid datastore. did you forget to pass args?");
    }
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
