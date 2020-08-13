// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QDebug>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <KPackage/PackageLoader>

#include "initialstart.h"

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
    QCoreApplication::setApplicationName(QStringLiteral("InitialStart"));

    KLocalizedString::setApplicationDomain("arkade");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("org.kde.plasma.initialstart"_L1, "Main"_L1);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
