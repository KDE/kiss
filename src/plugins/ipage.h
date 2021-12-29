#pragma once

#include <QtPlugin>
#include <QQmlPropertyMap>
#include <Croutons/Future>
#include <KPluginMetaData>

class QQuickItem;
class QQmlEngine;
class KISS;
class QQmlPropertyMap;

class Page : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool canGoNext READ canGoNext NOTIFY canGoNextChanged)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString subtitle READ subtitle CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* dataStore READ dataStore CONSTANT)

    QQmlPropertyMap* m_dataStore;

public:
    explicit Page(QObject* parent = nullptr, const KPluginMetaData& md = {}, const QVariantList& args = {});
    virtual ~Page();

    virtual QString title() const = 0;
    virtual QString subtitle() const = 0;

    virtual QQuickItem* createItem(QQmlEngine* engine) = 0;
    virtual Croutons::FutureResult<> apply() = 0;

    QQmlPropertyMap* dataStore() const { return m_dataStore; }

    virtual bool canGoNext() const = 0;
    Q_SIGNAL void canGoNextChanged();

};

QQuickItem* createItemFromURL(const QString& uri, QQmlEngine* eng, QObject* ctxt);
