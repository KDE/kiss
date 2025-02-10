// SPDX-FileCopyrightText: 2024 Devin Lin <devin@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "initialstartmodule.h"

InitialStartModule::InitialStartModule(QObject *parent)
    : QObject{parent}
{
}

bool InitialStartModule::nextEnabled() const
{
    return m_nextEnabled;
}

void InitialStartModule::setNextEnabled(bool nextEnabled)
{
    if (m_nextEnabled == nextEnabled) {
        return;
    }
    m_nextEnabled = nextEnabled;
    Q_EMIT nextEnabledChanged();
}

bool InitialStartModule::available() const
{
    return m_available;
}

void InitialStartModule::setAvailable(bool available)
{
    if (m_available == available) {
        return;
    }
    m_available = available;
    Q_EMIT availableChanged();
}

QQuickItem *InitialStartModule::contentItem() const
{
    return m_contentItem;
}

void InitialStartModule::setContentItem(QQuickItem *contentItem)
{
    if (m_contentItem == contentItem) {
        return;
    }
    m_contentItem = contentItem;
    Q_EMIT contentItemChanged();
}

qreal InitialStartModule::cardWidth() const
{
    return m_cardWidth;
}

void InitialStartModule::setCardsWith(qreal cardWidth)
{
    if (m_cardWidth == cardWidth) {
        return;
    }
    m_cardWidth = cardWidth;
    Q_EMIT cardWidthChanged();
}

QQmlListProperty<QObject> InitialStartModule::children()
{
    return QQmlListProperty<QObject>(this, &m_children);
}
