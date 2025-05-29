// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QQmlEngine>

/**
 * @brief Handles keyboard layout choice.
 *
 * This class provides functionality to load available keyboard layouts,
 * set the current layout, and apply the selected layout.
 *
 * Layout choice applies to this application, as well as either the live session or
 * the newly created user depending on the context of how we are running.
 */
class KeyboardUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QStringList availableLayouts READ availableLayouts NOTIFY availableLayoutsChanged)
    Q_PROPERTY(QString currentLayout READ currentLayout WRITE setCurrentLayout NOTIFY currentLayoutChanged)

public:
    explicit KeyboardUtil(QObject *parent = nullptr);

    QStringList availableLayouts() const;
    QString currentLayout() const;
    void setCurrentLayout(const QString &layout);

    Q_INVOKABLE void applyLayout();

Q_SIGNALS:
    void availableLayoutsChanged();
    void currentLayoutChanged();

private:
    void loadAvailableLayouts();

    QStringList m_availableLayouts;
    QString m_currentLayout;
};
