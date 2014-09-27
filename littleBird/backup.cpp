#include "backup.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QQuickView>
#include <windows.h>
#include <QUrl>
#include <QXmlStreamWriter>

backup::backup(QObject *parent) :
    QObject(parent)
{
}
extern QString  configContent;
void backup::backupfile(QList<QUrl> taregetFile, QString targetDir, QString applicationDirPath)
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

        QString targetDirWithoutPrefix = configContent.mid(8);

        QString saveDirUrl(targetDirWithoutPrefix+"/"+current_date);
        QDir saveDir(saveDirUrl);
//create  mk
        if(!saveDir.exists()){
            saveDir.mkpath(saveDirUrl);
        }
//copyAndRemove
        bool copyFlag = QFile::copy(sourceUrl, saveDirUrl+"/"+fileName);
        bool removeFlag;
        if(copyFlag){
            removeFlag = QFile::remove(sourceUrl);
        }
 //log
        QString log;
        if(copyFlag && removeFlag){
            log = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" SUCCESS! "+"  copyFile:"+url+"  to: "+saveDirUrl+"\r\n";
        }
        else{
            if(copyFlag){
                log = "##\r\n"+current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" DELETE FILE ERROR! "+"  copyFile:"+url+"  to: "+saveDirUrl+"\r\n##\r\n";
            }
            else{
                log = "##\r\n"+current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz")+" COPY ERROR! "+"  copyFile:"+url+"  to: "+saveDirUrl+"\r\n##\r\n";
            }
        }

        std::string str2 = applicationDirPath.toStdString();
        const char* msg2 = str2.c_str();
qDebug(msg2);
        QFile logFile(applicationDirPath+"/log.log");

        if(logFile.open(QIODevice::Append)){
            qDebug("open logFile success ");
        }
        else{
            qDebug("open logFile fails");
        }

        //Qstring to char *  support simplified chinese
        std::string str = log.toStdString();
        const char* msg = str.c_str();
        logFile.write(msg, qstrlen(msg));

        logFile.close();
    }
    //Sleep(5000);

    emit backupfileCompleted();
}

void backup::saveConfigured(QString taregetFile, QString applicationDirPath)
{
     QFile file(applicationDirPath+"/config.xml");
    if(file.open(QIODevice::WriteOnly)){
        qDebug("open configFile for change success ");
    }
    else{
        qDebug("open configFile for change fails");
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("dir");
    writer.writeTextElement("targetDir",taregetFile);
    writer.writeEndDocument();
    writer.writeEndDocument();
    file.close();

    configContent=taregetFile;

    emit configuredHadSaved();
}

//void backup::openConfiguredWin()
//{
//    QQuickView *view = new QQuickView;
//    view->setSource(QUrl::fromLocalFile("D:/Users/yjh/qt/untitled/configuration.qml"));
//    view->setFlags(Qt::FramelessWindowHint);
//    int ss(view->status());
//    if(ss==2){
//        qDebug("Loading");
//    }else{

//        view->show();
//    }
//    //emit readConfiguredMess(fromFile,taregetFile);
//}
