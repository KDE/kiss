// SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QQmlEngine>

struct Layout {
    QString name;
    QString variant;
};

/**
 * Handles keyboard layout choice.
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

public:
    explicit KeyboardUtil(QObject *parent = nullptr);

    /**
     * Sets the keyboard layout.
     *
     * @param layout The short name of the keyboard layout to set, e.g., "us", "de", etc.
     * @param variant The variant of the keyboard layout (optional).
     */
    Q_INVOKABLE void setLayout(const QString &layout, const QString &variant = QString());

private:
    /**
     * Applies the currently set keyboard layout.
     */
    void applyLayout();

    /**
     * Applies the currently set keyboard layout for the current user.
     */
    void applyLayoutForCurrentUser();

    /**
     * Applies the currently set keyboard layout as the system default.
     */
    void applyLayoutAsSystemDefault();

    Layout m_layout;
};
