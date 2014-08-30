#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backup.h"
#include <QtQml>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
qmlRegisterType<backup>("com.backup", 1, 0, "Backup");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
