#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <exception>

#include "src/Ui/message_strs.h"
#include "src/MysqlExe/mysql_exe.h"

class login_ui :public QDialog{
    Q_OBJECT
private:
    QLabel *label1,*label2,*label3,*label4;
    QLineEdit *hostNameEdit,*userNameEdit,*passwordEdit;
    QVBoxLayout *mainLayout;
    QPushButton *loginButton;
    mysql_exe *theSql;
public:
    const static int MAIN_WIDTH = 298;
    const static int MAIN_HEIGHT = 200;
    const static int ROW_HEIGHT = 20;
    const static int LABEL_WIDTH = 65;
    const static int EDIT_WIDTH = 200;
    const static int MESSAGE_LINE_HEIGHT = 10;
    login_ui(mysql_exe *sql,QWidget *father);
    QHBoxLayout *getSubLayout(QLabel *&label,\
                        QLineEdit *&edit,const QString &labelWord);
    QPushButton *getLoginButton();
    QLabel *getMessageArea();
    void slotConnectInit();
public slots:
    void pressLoginButton();
};

#endif // LOGIN_UI_H
