#include <KPluginFactory>
#include <KLocalizedString>

#include <crack.h>

#include "samplepage.h"

K_PLUGIN_CLASS_WITH_JSON(SamplePage, "page_sample.json")

SamplePage::SamplePage(QObject* parent, const KPluginMetaData& data, const QVariantList& args) : Page(parent, data, args)
{
}

SamplePage::~SamplePage()
{

}


QString SamplePage::title() const
{
    return i18n("Sample Page");
}

QString SamplePage::subtitle() const
{
    return i18n("This is an example page");
}

QQuickItem* SamplePage::createItem(QQmlEngine* engine)
{
    return createItemFromURL("qrc:/SamplePage.qml", engine, this);
}

/**
 * This is called at the end of initial system setup
 * to apply whatever changes were specified
 * by the user.
 *
 * Croutons has a coroutine_integration header,
 * which you can use to co_await asynchronous operations.
 *
 * If you're not doing anything async, you can just return
 * a succeeded nil future.
 */
Croutons::FutureResult<> SamplePage::apply()
{
    auto ret = Croutons::FutureResult<>();
    ret.succeed(Croutons::Nil{});
    return ret;
}

bool SamplePage::canGoNext() const
{
    return m_canNext;
}

void SamplePage::setCanGoNext(bool val)
{
    m_canNext = val;
    Q_EMIT canGoNextChanged();
}

#include "samplepage.moc"
