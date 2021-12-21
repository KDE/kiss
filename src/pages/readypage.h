#pragma once

#include "plugins/ipage.h"

class ReadyPage : public Page
{

    Q_OBJECT

public:

    explicit ReadyPage(KISS* kiss, QObject* parent = nullptr);
    ~ReadyPage();

    QString title() const override;
    QString subtitle() const override;

    QQuickItem* createItem(QQmlEngine* engine) override;
    Croutons::FutureResult<> apply() override;

    bool canGoNext() const override;

};