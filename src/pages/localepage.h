#pragma once

#include "plugins/ipage.h"

struct Language
{
	Q_GADGET

public:
	Q_PROPERTY(QString name MEMBER m_name CONSTANT)
	QString m_name;

	Q_PROPERTY(QString code MEMBER m_code CONSTANT)
	QString m_code;
};

class LocalePage : public Page
{

    Q_OBJECT
    Q_PROPERTY(QVariantList locales READ locales CONSTANT)

    QVariantList m_locales;

public:

    explicit LocalePage(QQmlPropertyMap* map, QObject* parent = nullptr);
    ~LocalePage();

    QString title() const override;
    QString subtitle() const override;

    QQuickItem* createItem(QQmlEngine* engine) override;
    Croutons::FutureResult<> apply() override;

    bool canGoNext() const override;

    QVariantList locales() const;

};