#include <KLocalizedString>

#include "localepage.h"

LocalePage::LocalePage(QQmlPropertyMap* map, QObject* parent) : Page(parent, {QVariant::fromValue(map)})
{
	auto locs = KLocalizedString::availableDomainTranslations("plasmashell").values();
	std::transform(locs.begin(), locs.end(), std::back_inserter(m_locales), [](const QString& locale) -> QVariant {
		return QVariant::fromValue(Language {
			.m_name = QLocale(locale).nativeLanguageName(),
			.m_code = locale
		});
	});
	std::sort(m_locales.begin(), m_locales.end(), [](const QVariant& lhs, const QVariant& rhs) -> bool {
		return lhs.value<Language>().m_name < rhs.value<Language>().m_name;
	});
}

LocalePage::~LocalePage()
{

}


QString LocalePage::title() const
{
    return i18n("Welcome");
}

QString LocalePage::subtitle() const
{
    return i18n("Select a language to begin setup");
}

QQuickItem* LocalePage::createItem(QQmlEngine* engine)
{
    return createItemFromURL("qrc:/LocalePage.qml", engine, this);
}

Croutons::FutureResult<> LocalePage::apply()
{
    auto ret = Croutons::FutureResult<>();
    ret.succeed(Croutons::Nil{});
    return ret;
}

QVariantList LocalePage::locales() const
{
    return m_locales;
}

bool LocalePage::canGoNext() const
{
    return true;
}
