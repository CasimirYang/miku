#include "backup.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QQuickView>
#include <windows.h>
backup::backup(QObject *parent) :
    QObject(parent)
{
}

void backup::backupfile(QString taregetFile)
{

    //   qDebug("Q--QQ");
    QString outputMess;
    QStringList list;
    list = taregetFile.split(",");
    QStringListIterator javaStyleIterator(list);
    while (javaStyleIterator.hasNext()){
        QString url(javaStyleIterator.next().toLocal8Bit().constData());


        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd");

        //cut out "file:///"
        QString sourceUrl = url.mid(8);

        int index = sourceUrl.lastIndexOf("/");
        QString fileName(sourceUrl.mid(index));

        QString saveTopDirUrl("X:/xx");
        QString saveDirUrl(saveTopDirUrl+"/"+current_date);
        QDir saveDir(saveDirUrl);
        if(!saveDir.exists()){
            saveDir.mkpath(saveDirUrl);
        }

        bool flag = QFile::copy(sourceUrl, saveDirUrl+"/"+fileName);

        // QFile::remove("X:/xx/psrbd.js");

        QString log;
        if(flag){
            log = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" SUCCESS! "+"  copyFile:"+url+"  toDir:"+fileName+"\r\n";
        }
        else{
            log = "##\r\n"+current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" ERROR! "+"  copyFile:"+url+"  toDir:"+fileName+"\r\n##\r\n";

        }
        //Qstring to char *  support simplified chinese
        std::string str = log.toStdString();
        const char* msg = str.c_str();

        //log
        QFile logFile(saveTopDirUrl+"/log.log");
        logFile.open(QIODevice::Append);
        logFile.write(msg, qstrlen(msg));
        logFile.close();


    }


    emit logMess(taregetFile);
}
void backup::openConfiguredWin()
{
    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile("D:/Users/yjh/qt/untitled/configuration.qml"));
    //view->setFlags(Qt::FramelessWindowHint);
    int ss(view->status());
    if(ss==2){
        qDebug("Loading");
    }else{

        view->show();
    }
    //emit readConfiguredMess(fromFile,taregetFile);

}

void backup::saveConfigured()
{
    emit configuredHadSaved();
}
