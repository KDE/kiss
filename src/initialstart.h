// SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <KPackage/Package>
#include <qqmlintegration.h>

#include "pagesmodel.h"

class QQmlEngine;
class QQuickItem;
class KLocalizedContext;


/**
 * Singleton class exposing global variables to the QML application.
 */
class InitialStart : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(PagesModel *pagesModel READ pagesModel NOTIFY pagesModelChanged)
    Q_PROPERTY(QString pageId READ pageId WRITE setPageId NOTIFY pageIdChanged)
    Q_PROPERTY(QQuickItem *pageItem READ pageItem NOTIFY pageItemChanged)

public:
    InitialStart(QObject *parent = nullptr);
    ~InitialStart() = default;

    PagesModel *pagesModel() const;
    void setPagesModel(PagesModel *pagesModel);

    QString pageId() const;
    void setPageId(const QString &pageId);

    QQuickItem *pageItem();
    QString qmlPath();

Q_SIGNALS:
    void pagesModelChanged();
    void pageIdChanged();
    void pageItemChanged();

private:
    QQuickItem *createGui(const QString &qmlPath);

    PagesModel *m_pagesModel;
    QQmlEngine *m_engine;
    KLocalizedContext *m_contextObj = nullptr;
    QString m_pageId;
    KPackage::Package m_pagePackage;
};
