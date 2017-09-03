#include "databases_display_ui.h"

databases_display_ui::databases_display_ui
    (mysql_exe *sql,int r,int c,int h){
    mainSql = sql;
    itemsCon = 0; disItems = 0;
    wids = new int[c];
    tits = new QString[c];
    tits[0] = DATABASE_DISPLAY_TIT1;
    wids[0] = CLO_WEIGHT1;
    for(int i=1;i<c;i++){
        tits[i] = (i==1)?DATABASE_DISPLAY_TIT2:"";
        wids[i] = CLO_WEIGHT2;
    }
    mainDis = new DatabasesDisplayUi(r,c,wids,h,tits);
    mainDis->addBorder();
    setQue();
}
databases_display_ui::~databases_display_ui(){
    deleteDis();
    delete mainDis;
    delete[] tits;
    delete[] wids;
}
void databases_display_ui::setQue(){
    QVector<QString*> v;
    QString *toAdd;
    QSqlQuery *que = new QSqlQuery();
    que->exec("show databases");
    while(que->next()){
        toAdd = new QString[mainDis->getCol()];
        toAdd[0] = que->value(0).toString();
        v.push_back(toAdd);
    }
    for(int i=0;i<v.size();i++){
        mainSql->use(v[i][0]);
        delete que; que = new QSqlQuery();
        que->exec("show tables");
        for(int j=0;que->next()&&j+1<(mainDis->getCol());j++){
            v[i][j+1] = que->value(0).toString();
        }
    }
    deleteDis();
    disItems = new QString*[v.size()];
    for(int i=0;i<v.size();i++){
        disItems[i] = new QString[mainDis->getCol()];
        for(int j=0;j<mainDis->getCol();j++){
            disItems[i][j] = v[i][j];
        }
    }
    itemsCon = v.size();
    mainDis->setDisplay(disItems,itemsCon,1);
    mainDis->display();
}
void databases_display_ui::show(){
    mainDis->show();
}
void databases_display_ui::deleteDis(){
    for(int i=0;i<itemsCon;i++){
        delete[] disItems[i];
    }
    delete[] disItems;
    disItems = 0;
    itemsCon = 0;
}

DatabasesDisplayUi::DatabasesDisplayUi(int r,int c,\
                        int *wids,int h,QString *tit)
                        :display_ui(r,c,wids,h,tit){
    fontInit();
    colorInit();
    setColFont(0,fontLeft);
    setRowFont(0,fontTop);
    for(int i=0;i<=ROW_COUNT;i++){
        setRowBackground(i,(i&1)?color1:color2);
    }
}
void DatabasesDisplayUi::fontInit(){
    fontTop.setFamily("simsun");
    fontTop.setPixelSize(15);
    fontTop.setItalic(1);
    fontTop.setBold(1);

    fontLeft.setFamily("simsun");
    fontLeft.setPixelSize(15);
    fontLeft.setBold(1);
}
void DatabasesDisplayUi::colorInit(){
    color1 = "#808A87";
    color2 = "#FAF0E6";
}
void DatabasesDisplayUi::rowClicked(int _r){
    qDebug() << "db dis " << (pageNow-1)*ROW_COUNT+_r-1;
}
