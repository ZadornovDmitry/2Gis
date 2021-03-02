#include <QApplication>
#include <QQmlApplicationEngine>
#include "repetitionscounter.h"
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    app.setOrganizationName("2Gis");

    app.setApplicationName("Test App");

    QQmlApplicationEngine engine;
    qmlRegisterType<RepetitionsCounter>("RepetitionsCounter", 1, 0, "RepetitionsCounter");

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
