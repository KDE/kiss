#include <KPluginFactory>
#include <KLocalizedString>
#include <QFile>

#include "licensepage.h"
#include "initialsystemsetuplicense.h"

K_PLUGIN_CLASS_WITH_JSON(LicensePage, "page_license.json")

struct LicensePage::Private
{
	bool canNext = false;
	QScopedPointer<Config> config;
	QString text;
};

LicensePage::LicensePage(QObject* parent, const KPluginMetaData& data, const QVariantList& args) : Page(parent, data, args), d(new Private)
{
	d->config.reset(new Config());

	QFile license(d->config->licenseTextFile());
	bool ok = license.open(QIODevice::ReadOnly);
	Q_ASSERT(ok);
	d->text = QString::fromUtf8(license.readAll());
}

LicensePage::~LicensePage()
{

}


QString LicensePage::title() const
{
	return i18n("Legal Terms");
}

QString LicensePage::subtitle() const
{
	return i18n("Let's get the legalese out of the way...");
}

QQuickItem* LicensePage::createItem(QQmlEngine* engine)
{
	return createItemFromURL("qrc:/LicensePage.qml", engine, this);
}

Croutons::FutureResult<> LicensePage::apply()
{
	auto ret = Croutons::FutureResult<>();
	ret.succeed(Croutons::Nil{});
	return ret;
}

bool LicensePage::canGoNext() const
{
	return d->canNext;
}

void LicensePage::setCanGoNext(bool val)
{
	if (d->canNext == val)
		return;

	d->canNext = val;
	Q_EMIT canGoNextChanged();
}

Qt::TextFormat LicensePage::textFormat() const
{
	switch (d->config->format()) {
	case Config::EnumFormat::HTML:
		return Qt::RichText;
	case Config::EnumFormat::Markdown:
		return Qt::MarkdownText;
	case Config::EnumFormat::PlainText:
	default:
		return Qt::PlainText;
	}
}

QString LicensePage::licenseText() const
{
	return d->text;
}

#include "licensepage.moc"
