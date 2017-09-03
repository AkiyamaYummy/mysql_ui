#ifndef MYSQL_EXE_H
#define MYSQL_EXE_H

#include <QtSql>

class mysql_exe{
public:
    const static QString LOGIN_SUCCESS;
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
    void use(QString dbName);
};

#endif // MYSQL_EXE_H
