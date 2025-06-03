// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedQmlContext>
#include <KLocalizedString>
#include <KPackage/PackageLoader>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
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

    KAboutData about(QStringLiteral("kiss"),
                     i18n("KDE Initial System Setup"),
                     QStringLiteral(KISS_VERSION_STRING),
                     i18n("Make Plasma yours"),
                     KAboutLicense::GPL_V3,
                     i18n("© 2021-2024 KDE Community"));

    QQmlApplicationEngine engine;

    {
        QCommandLineParser parser;
        about.setupCommandLine(&parser);
        parser.process(app);
        about.processCommandLine(&parser);
    }

    KLocalization::setupLocalizedContext(&engine);
    engine.loadFromModule("org.kde.initialsystemsetup"_L1, "Main"_L1);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
