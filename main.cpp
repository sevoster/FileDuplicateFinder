#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "duplicatesmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    DuplicatesModel model;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("duplicateModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
