#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backup.h"
#include <QtQml>
#include <QFile>
#include <QXmlStreamReader>
#include<QQuickView>
#include<QString>
#include<QCoreApplication>

//saveFile url
QString  configContent;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<backup>("com.backup", 1, 0, "Backup");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    // app.setWindowIcon(QIcon("D:/Users/yjh/qt/littleBird/images/2.ico"));

    QString runPath = QCoreApplication::applicationDirPath();
     QFile file(runPath+"/config.xml");
     if(!file.exists()){
        backup bp;
        bp.saveConfigured("file:///"+runPath,runPath);
     } ;
     if(file.open(QIODevice::ReadWrite)){
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
     file.close();

   configContent=text;

    engine.rootContext()->setContextProperty(QStringLiteral("targetDir"),text);
    engine.rootContext()->setContextProperty(QStringLiteral("applicationDirPath"),runPath);


    //    QQuickView viwer;
    //    viwer.setFlags(Qt::FramelessWindowHint);
    //    viwer.setColor(QColor(Qt::transparent));
    //    viwer.setSource(QUrl("qrc:///main.qml"));
    //    viwer.show();
    //viwer.rootContext()->setContextProperty("mainwindow",&viwer);

    return app.exec();



}
