// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QCommandLineParser>

#include "kiss.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setSetuidAllowed(true);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	QCommandLineParser parser;
	QCommandLineOption mobileOpt("m", "mobile");
	parser.addOption(mobileOpt);
	parser.process(app);

	QUrl url;
	if (parser.isSet(mobileOpt)) {
		url = QStringLiteral("qrc:/MobileMain.qml");
		QQuickStyle::setStyle("plasma");
	} else {
		url = QStringLiteral("qrc:/main.qml");
		QQuickStyle::setStyle("org.kde.desktop");
	}

	qmlRegisterUncreatableType<KISS>("org.kde.plasma.plasmoid", 2, 0, "KISS", "dummy register to get PlasmoidHeading working");

	QQmlApplicationEngine engine;
	QScopedPointer<KISS> kiss(new KISS(&engine));
	engine.rootContext()->setContextProperty("KISS", kiss.data());
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl) {
				QCoreApplication::exit(-1);
			}
		},
		Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
