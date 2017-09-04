#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVector>
#include <qdebug.h>

#include "src/UiTool/ExQLabel.h"
/*

Temporary version, read all the items at once.

*/
class display_ui :public QWidget{
    Q_OBJECT
protected:
    int ROW_COUNT,COL_COUNT,*SUB_WIDTHS,ROW_HEIGHT;
    int ITEM_COUNT;
    int MID_BORDER,EDGE_BORDER;
    int MAX_PAGE,BEST_RANK;
    int LETTER_WIDTH,PAGE_BUTTON_BLOCK;
    QString BORDER_COLOR;
    int pageNow;
    bool _hasPageNum;
    // release outside
    QString **displayStrs,*titles;
    // release inside
    ExQLabel **labels;
    QVBoxLayout *mainLayout;
    QHBoxLayout *pageNumLayout;
    QSignalMapper *mainMapper,*pageMapper;
    QVector<QWidget*> toDelete;
public:
    display_ui();
    display_ui(int r,int c,int *wids,\
               int h,QString *tit);
    void reInit(int r,int c,int *wids,\
                int h,QString *tit);
    ~display_ui();
    //mainBlockSet.
    QVBoxLayout *getLabelsLayout();
    //displayBlockSet.
    void display(int page = 1);
    void setDisplay(QString **dis,int itemCon,\
                    bool memoryReleaseFlag);
    //pageNumSet.
    void pageNumDisplay(int page);
    void setPageNumLayout(int page);
    QPushButton *getPageNumButton(int page,\
            QSignalMapper *mapper,QString text = "");
    void setPageNum(int m,int b);
    void setPageButton(int w,int b);
    //Border
    void addBorder(int m=1,int e=3,QString c="#696969");
    QString getBorderStr(int x,int y);
    void clearPageNumLayouyt();
    void clearMainLayout();
    int getCol();
    void setRowFont(int r,QFont &f);
    void setColFont(int c,QFont &f);
    void setRowBackground(int r, QString color);
    void setColBackground(int c, QString color);
    virtual void rowClicked(int _r);
public slots:
    void rowClickedSlot(int _r);
    void displaySlot(int page);
};

#endif // DISPLAY_UI_H
