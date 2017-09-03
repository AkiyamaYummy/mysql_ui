#include "display_ui.h"

/*
    // release outside
    QString **displayStrs,*titles;
    // release inside
    ExQLabel **labels;
    QVBoxLayout *mainLayout;
    QHBoxLayout *pageNumLayout;
    QSignalMapper *mainMapper,*pageMapper;
    QVector<QWidget*> toDelete;
*/

display_ui::display_ui(int r,int c,int *wids,int h,QString *tit){
    ITEM_COUNT = 0; displayStrs = 0;
    MAX_PAGE = 6; BEST_RANK = 3;
    LETTER_WIDTH = 7; PAGE_BUTTON_BLOCK = 4;
    _hasPageNum = 0;
    mainMapper = pageMapper = 0;
    displayStrs = 0;

    ROW_COUNT = r; COL_COUNT = c;
    SUB_WIDTHS = wids; ROW_HEIGHT = h;
    titles = tit;
    mainLayout = getLabelsLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    pageNumLayout = new QHBoxLayout();
    mainLayout->addLayout(pageNumLayout);
    setLayout(mainLayout);
    pageNow = 1;

    display();
}
display_ui::~display_ui(){
    clearMainLayout();
    mainLayout->deleteLater();
    mainLayout = 0;
    if(mainMapper){
        mainMapper->deleteLater();
        mainMapper = 0;
    }
    if(pageMapper){
        pageMapper->deleteLater();
        pageMapper = 0;
    }
}
//mainBlockSet.
QVBoxLayout *display_ui::getLabelsLayout(){
    QVBoxLayout *res = new QVBoxLayout();
    QHBoxLayout *row;

    if(mainMapper)mainMapper->deleteLater();
    mainMapper = new QSignalMapper(this);

    labels = new ExQLabel*[ROW_COUNT+1];
    for(int i=0;i<=ROW_COUNT;i++){
        labels[i] = new ExQLabel[COL_COUNT];
        row = new QHBoxLayout();
        row->setMargin(0);
        for(int j=0;j<COL_COUNT;j++){
            labels[i][j].setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            labels[i][j].setMinimumSize
                    (SUB_WIDTHS[j],ROW_HEIGHT);
            labels[i][j].setText(i?"":titles[j]);
            row->addWidget(&labels[i][j]);
            if(i != 0){
                mainMapper->setMapping(&labels[i][j],i);
                connect(&labels[i][j],SIGNAL(clicked())
                        ,mainMapper,SLOT(map()));
            }
        }
        res->addLayout(row);
    }
    connect(mainMapper,SIGNAL(mapped(int))
            ,this,SLOT(rowClickedSlot(int)));
    return res;
}
void display_ui::clearMainLayout(){
    for(int i=0;i<ROW_COUNT;i++)delete[] labels[i];
    delete[] labels;
    clearPageNumLayouyt();
    pageNumLayout->deleteLater();
    pageNumLayout = 0;
    while(mainLayout->count())
        delete mainLayout->takeAt(0);
}
//displayBlockSet.
void display_ui::display(int page){
    pageNumDisplay(page);
    for(int i=0;i<ROW_COUNT;i++){
        int r = (pageNow-1)*ROW_COUNT+i;
        if(r >= ITEM_COUNT){
            for(int j=i;j<ROW_COUNT;j++)
                for(int k=0;k<COL_COUNT;k++)
                    labels[j+1][k].setText("");
            break;
        }
        for(int j=0;j<COL_COUNT;j++){
            labels[i+1][j].setText(displayStrs[r][j]);
        }
    }
}
void display_ui::setDisplay(QString **dis,int itemCon,bool memoryReleaseFlag){
    if(memoryReleaseFlag && displayStrs){
        for(int i=0;i<ITEM_COUNT;i++){
            delete[] (displayStrs[i]);
            displayStrs[i] = 0;
        }
        delete[] displayStrs;
        displayStrs = 0;
    }
    displayStrs = dis;
    ITEM_COUNT = itemCon;
}
//pageNumSet.
void display_ui::pageNumDisplay(int page){
    clearPageNumLayouyt();
    setPageNumLayout(page);
}
void display_ui::clearPageNumLayouyt(){
    for(int i=0;i<toDelete.size();i++){
        delete toDelete[i];
        toDelete[i] = 0;
    }
    toDelete.clear();
    while(pageNumLayout->count())
        delete pageNumLayout->takeAt(0);
}
void display_ui::setPageNumLayout(int page){
    int tot = ITEM_COUNT/ROW_COUNT+(ITEM_COUNT%ROW_COUNT?1:0);
    if(tot < 1)tot = 1;
    if(page < 1)page = 1; if(page > tot)page = tot;
    pageNow = page;
    int sta,end;
    if(tot <= MAX_PAGE){
        sta = 1; end = tot;
    }else{
        sta = pageNow-BEST_RANK+1;
        if(sta+MAX_PAGE-1 > tot)sta = tot-MAX_PAGE+1;
        else if(sta < 1)sta = 1;
        end = sta+MAX_PAGE-1;
    }

    if(pageMapper)pageMapper->deleteLater();
    pageMapper = new QSignalMapper();

    pageNumLayout->addStretch();
    pageNumLayout->addWidget(getPageNumButton(1,pageMapper,"first"));
    pageNumLayout->addWidget(getPageNumButton
               ((1>pageNow-1)?1:(pageNow-1),pageMapper,"prev"));
    for(int i=sta;i<=end;i++){
        pageNumLayout->addWidget(getPageNumButton(i,pageMapper));
    }
    pageNumLayout->addWidget(getPageNumButton
               ((tot<pageNow+1)?tot:(pageNow+1),pageMapper,"next"));
    pageNumLayout->addWidget(getPageNumButton(tot,pageMapper,"last"));
    pageNumLayout->addStretch();
    connect(pageMapper,SIGNAL(mapped(int)),this,SLOT(displaySlot(int)));
}
QPushButton *display_ui::getPageNumButton(int page,QSignalMapper *mapper,\
                              QString text){
    if(!text.length())text = QString::number(page);
    QPushButton *res = new QPushButton(this);
    if(page == pageNow)res->setEnabled(false);
    res->setMaximumHeight(ROW_HEIGHT);
    res->setFixedWidth
            (text.length()*LETTER_WIDTH+PAGE_BUTTON_BLOCK);
    res->setText(text);
    mapper->setMapping(res,page);
    connect(res,SIGNAL(clicked()),mapper,SLOT(map()));
    toDelete.push_back(res);
    return res;
}
void display_ui::setPageNum(int m,int b){
    MAX_PAGE = m; BEST_RANK = b;
}
void display_ui::setPageButton(int w,int b){
    LETTER_WIDTH = w; PAGE_BUTTON_BLOCK = b;
}
//Border
void display_ui::addBorder(int m,int e,QString c){
    MID_BORDER = m; EDGE_BORDER = e;
    BORDER_COLOR = c;
    for(int i=0;i<=ROW_COUNT;i++)
        for(int j=0;j<COL_COUNT;j++){
            QString ss(labels[i][j].styleSheet());
            ss.append(getBorderStr(i,j));
            labels[i][j].setStyleSheet(ss);
        }
}
QString display_ui::getBorderStr(int x,int y){
    int l,r,t,b;
    l = t = 0; r = b = MID_BORDER;
    if(x == 0)t = EDGE_BORDER;
    if(y == 0)l = EDGE_BORDER;
    if(x == ROW_COUNT)b = EDGE_BORDER;
    if(y == COL_COUNT-1)r = EDGE_BORDER;
    QString res;
    res.append(QString("border-top : %1px solid %2;")
               .arg(t).arg(BORDER_COLOR));
    res.append(QString("border-bottom : %1px solid %2;")
               .arg(b).arg(BORDER_COLOR));
    res.append(QString("border-left : %1px solid %2;")
               .arg(l).arg(BORDER_COLOR));
    res.append(QString("border-right : %1px solid %2;")
               .arg(r).arg(BORDER_COLOR));
    return res;
}
void display_ui::setRowFont(int r,QFont &f){
    for(int c=0;c<COL_COUNT;c++){
        labels[r][c].setFont(f);
    }
}
void display_ui::setColFont(int c,QFont &f){
    for(int r=0;r<=ROW_COUNT;r++){
        labels[r][c].setFont(f);
    }
}
void display_ui::setRowBackground(int r,QString color){
    for(int c=0;c<COL_COUNT;c++){
        QString ss = labels[r][c].styleSheet();
        ss.append(QString("background-color: %1 ;").arg(color));
        labels[r][c].setStyleSheet(ss);
    }
}
void display_ui::setColBackground(int c,QString color){
    for(int r=0;r<ROW_COUNT;r++){
        QString ss = labels[r][c].styleSheet();
        ss.append(QString("background-color: %1 ;").arg(color));
        labels[r][c].setStyleSheet(ss);
    }
}
void display_ui::rowClickedSlot(int _r){
    this->rowClicked(_r);
}
void display_ui::rowClicked(int _r){
    qDebug() << "dis " << _r;
}
void display_ui::displaySlot(int page){
    display(page);
}
int display_ui::getCol(){
    return COL_COUNT;
}
