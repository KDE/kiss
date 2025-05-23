// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <KPackage/PackageLoader>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>

#include "../kiss-version.h"

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("org.kde.initialsystemsetup");

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

    KAboutData about(QStringLiteral("tokodon"),
                     i18n("Tokodon"),
                     QStringLiteral(KISS_VERSION_STRING),
                     i18n("Browse the Fediverse"),
                     KAboutLicense::GPL_V3,
                     i18n("© 2021-2024 KDE Community"));

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("org.kde.initialsystemsetup"_L1, "Main"_L1);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
