#pragma once

#include <KPluginMetaData>
#include "ipage.h"

class LicensePage : public Page
{

	Q_OBJECT

	struct Private;
	QScopedPointer<Private> d;

public:

	explicit LicensePage(QObject* parent, const KPluginMetaData& data, const QVariantList& args);
	~LicensePage();

	QString title() const override;
	QString subtitle() const override;

	QQuickItem* createItem(QQmlEngine* engine) override;
	Croutons::FutureResult<> apply() override;

	bool canGoNext() const override;
	Q_INVOKABLE void setCanGoNext(bool val);

	Q_PROPERTY(Qt::TextFormat textFormat READ textFormat CONSTANT)
	Qt::TextFormat textFormat() const;

	Q_PROPERTY(QString licenseText READ licenseText CONSTANT)
	QString licenseText() const;

};
