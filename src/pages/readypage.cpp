#include <KLocalizedString>

#include "readypage.h"

ReadyPage::ReadyPage(QQmlPropertyMap* map, QObject* parent) : Page(parent, {}, {QVariant::fromValue(map)})
{

}

ReadyPage::~ReadyPage()
{

}


QString ReadyPage::title() const
{
    return QString();
}

QString ReadyPage::subtitle() const
{
    return QString();
}

QQuickItem* ReadyPage::createItem(QQmlEngine* engine)
{
    return createItemFromURL("qrc:/ReadyPage.qml", engine, this);
}

Croutons::FutureResult<> ReadyPage::apply()
{
    auto ret = Croutons::FutureResult<>();
    ret.succeed(Croutons::Nil{});
    return ret;
}

bool ReadyPage::canGoNext() const
{
    return true;
}
