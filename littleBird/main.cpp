#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backup.h"
#include <QtQml>
#include <QFile>
#include <QXmlStreamReader>
#include<QQuickView>

int main(int argc, char *argv[])
{


    QFile file("D:/Users/yjh/qt/littleBird/config.xml");
    if(file.open(QIODevice::ReadOnly)){
        qDebug("open configFile success");
    }
    else{
        qDebug("open configFile fails");
    }
    QString text;
    QXmlStreamReader xml;
    xml.setDevice(&file);
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "targetDir"){
                text =  xml.readElementText();
            }
        }
    }
    QGuiApplication app(argc, argv);
    qmlRegisterType<backup>("com.backup", 1, 0, "Backup");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    //  app.setWindowIcon(QIcon("D:/Users/yjh/qt/littleBird/images/ico.ico"));
    engine.rootContext()->setContextProperty(QStringLiteral("targetDir"),text);



    //    QQuickView viwer;
    //    viwer.setFlags(Qt::FramelessWindowHint);
    //    viwer.setColor(QColor(Qt::transparent));
    //    viwer.setSource(QUrl("qrc:///main.qml"));
    //    viwer.show();
    //viwer.rootContext()->setContextProperty("mainwindow",&viwer);

    return app.exec();



}
