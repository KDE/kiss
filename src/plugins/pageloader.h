#pragma once

#include "ipage.h"

class QQmlPropertyMap;

QSharedPointer<Page> loadPage(const QString& name, QQmlPropertyMap* store);
