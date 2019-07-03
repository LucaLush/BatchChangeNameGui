#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->setFixedSize(420,321);
    ui->setupUi(this);
    ui->regExLine->setText("\\[.*\\]");//正则表达式删除中括号内容，显示出来斜杠会少一个
    qDebug()<<"main ThreadId"<<QThread::currentThreadId();
    F.moveToThread(&workerThread);
    connect(&workerThread,&QThread::finished,this,&Widget::showIfThreadFin);
    connect(this,&Widget::addSignal,&F,&FileControl::addRename);
    connect(this,&Widget::rxSignal,&F,&FileControl::rxRename);
    //进程消亡时通知我
    workerThread.start();
}

Widget::~Widget()
{
    delete ui;
    workerThread.quit();
    workerThread.wait();
}

void Widget::on_changeNameButton_clicked()//文件名前添加东西
{

    addSignal(ui->headAddLine->text());
}

void Widget::on_openDirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "C:/Users/QZL/Documents/QTProject/changeFileName",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);

    qDebug()<<"工作路径:"<<dir;
    F.getPath(dir);//获取工作路径
}

void Widget::on_changeNameModButton_clicked()//模板匹配删除字符
{

    rxSignal(ui->regExLine->text());

}

void Widget::showIfThreadFin()
{
    qDebug()<<"The New Thread Finised";
}

