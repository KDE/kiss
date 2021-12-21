#pragma once

#include <QtPlugin>
#include <Croutons/Future>

class QQuickItem;
class QQmlEngine;
class KISS;

class Page : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool canGoNext READ canGoNext NOTIFY canGoNextChanged)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString subtitle READ subtitle CONSTANT)

public:
    explicit Page(KISS* kiss, QObject* parent = nullptr);
    virtual ~Page();

    virtual QString title() const { qFatal("unimplemented title"); };
    virtual QString subtitle() const { qFatal("unimplemented subtitle"); };

    virtual QQuickItem* createItem(QQmlEngine* engine) { qFatal("unimplemented item"); };
    virtual Croutons::FutureResult<> apply() { qFatal("unimplemented apply"); };

    virtual bool canGoNext() const { qFatal("unimplemented cangonext"); };
    Q_SIGNAL void canGoNextChanged();

};

QQuickItem* createItemFromURL(const QString& uri, QQmlEngine* eng, QObject* ctxt);
