#include "mysql_exe.h"

const QString mysql_exe::DEFAULT_CONNECTION_NAME =
        "qt_sql_default_connection";
const QString mysql_exe::CONNECTION_NAME_TO_ADD =
        "QMYSQL";

mysql_exe::mysql_exe(){
    if(QSqlDatabase::contains(DEFAULT_CONNECTION_NAME)){
        single =
            QSqlDatabase::database(DEFAULT_CONNECTION_NAME);
    }else {
        single =
            QSqlDatabase::addDatabase(CONNECTION_NAME_TO_ADD);
    }
    _hadLogin = 0;
}
QString mysql_exe::login(QString hostname,\
                         QString username, QString password){
    single.setUserName(username);
    single.setPassword(password);
    single.setHostName(hostname);
    if(!single.open()){
        QString errmes = single.lastError().databaseText();
        return errmes;
    }else{
        _hadLogin = 1;
        return message_strs::LOGIN_SUCCESS;
    }
}
//warning
void mysql_exe::close(){
    single.close();
    QSqlDatabase::removeDatabase(single.connectionName());
}
bool mysql_exe::getHadLogin(){
    return _hadLogin;
}
