#include <QApplication>
#include <QtSql>

#include "src/Ui/message_strs.h"
#include "src/MysqlExe/mysql_exe.h"
#include "src/Ui/login_ui.h"
#include "src/UiTool/display_ui.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    a.setStyle("windows");

    /*
    mysql_exe *mainSql = new mysql_exe();
    QWidget *mainWidget = new database_display_ui();
    QDialog *loginUi = new login_ui(mainSql,mainWidget);

    if(loginUi->exec()==QDialog::Accepted){
        QSqlQuery que;
        que.exec("show databases");
        //while(que.next())
            //qDebug() << que.value(0).toString();
        mainWidget->show();
        return a.exec();
    }else return 0;
    */

    int wids[5] = {100,100,100,100,100};
    QString tits[5] = {"titdemo1","titdemo2","titdemo3","titdemo4","titdemo5"};
    display_ui *m = new display_ui(10,5,wids,20,tits);
    int itemCon = 83;
    QString **dis = new QString*[itemCon];
    for(int i=0;i<itemCon;i++){
        dis[i] = new QString[5];
        for(int j=0;j<5;j++)
            dis[i][j] = QString("row %1 - col %2").arg(i+1).arg(j+1);
    }
    m->setBorder(1,3,"#696969");
    m->setDisplay(dis,itemCon,true);
    m->display(2);
    m->show();
    return a.exec();
}
