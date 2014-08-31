#include "backup.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QQuickView>
#include <windows.h>
#include <QUrl>
backup::backup(QObject *parent) :
    QObject(parent)
{
}

void backup::backupfile(QList<QUrl> taregetFile, QString targetDir)
{

    QString outputMess;

    QListIterator<QUrl> iterator(taregetFile);
    while (iterator.hasNext()) {
        QString url(iterator.next().toString());
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd");

        //cut out "file:///"
        QString sourceUrl = url.mid(8);
        int index = sourceUrl.lastIndexOf("/");
        QString fileName(sourceUrl.mid(index+1));
        QString saveDirUrl(targetDir+"/"+current_date);

        QDir saveDir(saveDirUrl);
        if(!saveDir.exists()){
            saveDir.mkpath(saveDirUrl);
        }
        bool copyFlag = QFile::copy(sourceUrl, saveDirUrl+"/"+fileName);
        bool removeFlag;
        if(copyFlag){
              removeFlag = QFile::remove(sourceUrl);
        }
        QString log;
        if(copyFlag && removeFlag){
            log = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" SUCCESS! "+"  copyFile:"+url+"  toDir:"+fileName+"\r\n";
        }
        else{
            if(copyFlag){
                 log = "##\r\n"+current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" DELETE FILE ERROR! "+"  copyFile:"+url+"  toDir:"+fileName+"\r\n##\r\n";
            }
            else{
                 log = "##\r\n"+current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" COPY ERROR! "+"  copyFile:"+url+"  toDir:"+fileName+"\r\n##\r\n";
            }
        }
        //Qstring to char *  support simplified chinese
        std::string str = log.toStdString();
        const char* msg = str.c_str();

        //log
        QFile logFile(targetDir+"/log.log");
        logFile.open(QIODevice::Append);
        logFile.write(msg, qstrlen(msg));
        logFile.close();
    }
    Sleep(5000);
    emit backupfileCompleted();
}
void backup::openConfiguredWin()
{
    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile("D:/Users/yjh/qt/untitled/configuration.qml"));
    view->setFlags(Qt::FramelessWindowHint);
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
