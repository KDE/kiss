#include <KPluginMetaData>
#include <KPluginFactory>

#include "pageloader.h"

QSharedPointer<Page> loadPage(const QString& name, QQmlPropertyMap* store)
{
    const auto md =
        KPluginMetaData::findPluginById("kisspages", name);

    if (!md.isValid())
        return nullptr;

    auto page =
        KPluginFactory::instantiatePlugin<Page>
            (md, nullptr, {QVariant::fromValue(store)});

    if (page)
        return QSharedPointer<Page>(page.plugin);

    return nullptr;
}
