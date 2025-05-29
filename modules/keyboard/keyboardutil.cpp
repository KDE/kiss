// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "keyboardutil.h"

#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QTextStream>

#include <qstringliteral.h>

KeyboardUtil::KeyboardUtil(QObject *parent)
    : QObject(parent)
{
}

QStringList KeyboardUtil::availableLayouts() const
{
    return m_availableLayouts;
}

QString KeyboardUtil::currentLayout() const
{
    return m_currentLayout;
}

void KeyboardUtil::setCurrentLayout(const QString &layout)
{
    if (m_currentLayout != layout) {
        m_currentLayout = layout;
        Q_EMIT currentLayoutChanged();
    }
}

void KeyboardUtil::applyLayout()
{
}

void KeyboardUtil::loadAvailableLayouts()
{
}
