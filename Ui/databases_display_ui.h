#ifndef DATABASES_DISPLAY_UI_H
#define DATABASES_DISPLAY_UI_H

#include <QSqlQuery>

#include "src/MysqlExe/mysql_exe.h"
#include "src/UiTool/display_ui.h"

class databases_display_ui :public display_ui{
public:
    const static QString DATABASE_DISPLAY_TIT1;
    const static QString DATABASE_DISPLAY_TIT2;
private:
    QFont fontTop,fontLeft,fontMain;
    QString color1,color2;
    // release outside
    mysql_exe *mainSql;
    // release inside
    QString *tits,**disItems;
    int *wids,itemsCon;
public:
    const static int CLO_WEIGHT1 = 170;
    const static int CLO_WEIGHT2 = 100;
    databases_display_ui
        (mysql_exe *sql,int r,int c,int h);
    ~databases_display_ui();
    void setQue();
    void deleteDis();
    void fontInit();
    void colorInit();
    void rowClicked(int _r);
};

#endif // DATABASES_DISPLAY_UI_H
