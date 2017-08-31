#ifndef MYSQL_EXE_H
#define MYSQL_EXE_H

#include <QtSql>

#include "src/Ui/message_strs.h"

class mysql_exe{
private:
    QSqlDatabase single;
    bool _hadLogin;
public:
    const static QString DEFAULT_CONNECTION_NAME;
    const static QString CONNECTION_NAME_TO_ADD;
    mysql_exe();
    QString login(QString a,QString b,QString c);
    void close();
    bool getHadLogin();
};

#endif // MYSQL_EXE_H
