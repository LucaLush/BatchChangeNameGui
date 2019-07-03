#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThread>
#include"filecontrol.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_changeNameButton_clicked();

    void on_openDirButton_clicked();

    void on_changeNameModButton_clicked();

    void showIfThreadFin();

private:
    Ui::Widget *ui;
    FileControl F;
    QThread workerThread;
signals:
    void addSignal(const QString&);
    void rxSignal(const QString&);

};

#endif // WIDGET_H
