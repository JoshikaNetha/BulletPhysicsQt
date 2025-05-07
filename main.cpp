#include <QGuiApplication>
#include <QQmlApplicationEngine>
// #include <Bullet.h>
#include "PhysicsEngine.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/BUlletPhysics/main.qml"));

    qmlRegisterType<PhysicsEngine>("PhysicsEngine", 1, 0, "PhysicsEngine");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    // Bullet bull;
    // bull.initialize();
    engine.load(url);

    return app.exec();
}
