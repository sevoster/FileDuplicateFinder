#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "duplicatefinder.h"

class Model : public QObject
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void initFinder(QString dir, bool recursive)
    {
        finder.reset(new DuplicateFinder(dir, recursive));
        QStringList list = finder->getFiles();
        printf("LIST: %s\n", list.join("  ").toStdString().c_str());
    }

    std::unique_ptr<DuplicateFinder> finder;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Model model;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
