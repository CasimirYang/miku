#ifndef BACKUP_H
#define BACKUP_H

#include <QObject>

class backup : public QObject
{
    Q_OBJECT
public:
    explicit backup(QObject *parent = 0);
signals:
    void  logMess(QString logmess);
    void  configuredHadSaved();
    void  readConfiguredMess(QString fromFile,QString taregetFile);
public slots:
    void  backupfile(QString taregetFile);
    void  openConfiguredWin(void);
    void saveConfigured();
};

#endif // BACKUP_H
