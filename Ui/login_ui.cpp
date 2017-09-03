#include "login_ui.h"

login_ui::login_ui(mysql_exe *sql,QWidget *father):QDialog(father){
    theSql = sql;

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(getSubLayout(label1,hostNameEdit,\
        LOGIN_HOSTNAME_TEXTLINE));
    mainLayout->addLayout(getSubLayout(label2,userNameEdit,\
        LOGIN_USERNAME_TEXTLINE));
    mainLayout->addLayout(getSubLayout(label3,passwordEdit,\
        LOGIN_PASSWORD_TEXTLINE));
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = getLoginButton();
    mainLayout->addWidget(loginButton);
    label4 = getMessageArea();
    mainLayout->addWidget(label4);

    QDialog();
    setFixedSize(MAIN_WIDTH,MAIN_HEIGHT);
    setLayout(mainLayout);
    setWindowTitle(LOGIN_TITLE);
    setFixedWidth(MAIN_WIDTH);

    slotConnectInit();
}
QHBoxLayout *login_ui::getSubLayout(QLabel *&label,\
                    QLineEdit *&edit,const QString &labelWord){
    label = new QLabel(this);
    label->setText(labelWord);
    edit = new QLineEdit(this);
    edit->setFixedSize(EDIT_WIDTH,ROW_HEIGHT);
    label->setFixedSize(LABEL_WIDTH,ROW_HEIGHT);
    QHBoxLayout *res = new QHBoxLayout();
    res->addWidget(label);
    res->addWidget(edit);
    return res;
}
QPushButton *login_ui::getLoginButton(){
    QPushButton *res = new QPushButton(this);
    res->setText(LOGIN_LOGIN_BUTTON);
    res->setFixedHeight(ROW_HEIGHT);
    return res;
}
QLabel *login_ui::getMessageArea(){
    QLabel *res = new QLabel();
    res->setWordWrap(true);
    res->setAlignment(Qt::AlignTop);
    res->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    res->setLineWidth(2);
    //res->setStyleSheet("border:1px solid black");
    return res;
}
void login_ui::slotConnectInit(){
    connect(loginButton,SIGNAL(clicked()),\
            this,SLOT(pressLoginButton()));
}
void login_ui::pressLoginButton(){
    label4->setText(LOGIN_WAITING);
    repaint();
    QString s1 = hostNameEdit->text();
    QString s2 = userNameEdit->text();
    QString s3 = passwordEdit->text();
    label4->setText(theSql->login(s1,s2,s3));
    if(theSql->getHadLogin())this->accept();
    repaint();
}
