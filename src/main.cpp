#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "kiss.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setSetuidAllowed(true);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	QScopedPointer<KISS> kiss(new KISS);

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

	QQmlApplicationEngine engine;
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
