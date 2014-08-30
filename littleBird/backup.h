#ifndef BACKUP_H
#define BACKUP_H

#include <QObject>

class backup : public QObject
{
    Q_OBJECT
public:
    explicit backup(QObject *parent = 0);

signals:

public slots:

};

#endif // BACKUP_H
