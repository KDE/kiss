#pragma once

#include <KPluginMetaData>
#include "ipage.h"

class SamplePage : public Page
{

    Q_OBJECT

    bool m_canNext = false;

public:

    explicit SamplePage(QObject* parent, const KPluginMetaData& data, const QVariantList& args);
    ~SamplePage();

    QString title() const override;
    QString subtitle() const override;

    QQuickItem* createItem(QQmlEngine* engine) override;
    Croutons::FutureResult<> apply() override;

    bool canGoNext() const override;
    Q_INVOKABLE void setCanGoNext(bool val);

};
