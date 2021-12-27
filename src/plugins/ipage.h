#pragma once

#include <QtPlugin>
#include <QQmlPropertyMap>
#include <Croutons/Future>

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
    explicit Page(QObject* parent = nullptr, const QVariantList& args = {});
    virtual ~Page();

    virtual QString title() const { qFatal("unimplemented title"); };
    virtual QString subtitle() const { qFatal("unimplemented subtitle"); };

    virtual QQuickItem* createItem(QQmlEngine* engine) { qFatal("unimplemented item"); };
    virtual Croutons::FutureResult<> apply() { qFatal("unimplemented apply"); };

    QQmlPropertyMap* dataStore() const { return m_dataStore; }

    virtual bool canGoNext() const { qFatal("unimplemented cangonext"); };
    Q_SIGNAL void canGoNextChanged();

};

QQuickItem* createItemFromURL(const QString& uri, QQmlEngine* eng, QObject* ctxt);
