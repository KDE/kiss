// SPDX-FileCopyrightText: 2024 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "initialstartmodule.h"

SetupModule::SetupModule(QObject *parent)
    : QObject{parent}
{
}

bool SetupModule::nextEnabled() const
{
    return m_nextEnabled;
}

void SetupModule::setNextEnabled(bool nextEnabled)
{
    if (m_nextEnabled == nextEnabled) {
        return;
    }
    m_nextEnabled = nextEnabled;
    Q_EMIT nextEnabledChanged();
}

bool SetupModule::available() const
{
    return m_available;
}

void SetupModule::setAvailable(bool available)
{
    if (m_available == available) {
        return;
    }
    m_available = available;
    Q_EMIT availableChanged();
}

QQuickItem *SetupModule::contentItem() const
{
    return m_contentItem;
}

void SetupModule::setContentItem(QQuickItem *contentItem)
{
    if (m_contentItem == contentItem) {
        return;
    }
    m_contentItem = contentItem;
    Q_EMIT contentItemChanged();
}

qreal SetupModule::cardWidth() const
{
    return m_cardWidth;
}

void SetupModule::setCardsWith(qreal cardWidth)
{
    if (m_cardWidth == cardWidth) {
        return;
    }
    m_cardWidth = cardWidth;
    Q_EMIT cardWidthChanged();
}

QQmlListProperty<QObject> SetupModule::children()
{
    return QQmlListProperty<QObject>(this, &m_children);
}
