#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QObject>
#include<QString>
#include<QDir>


class FileControl : public QObject
{
    Q_OBJECT
public:
    explicit FileControl(QObject *parent = nullptr);
    void getPath(const QString&);//获取文件夹路径

signals:

public slots:
    void rxRename(const QString&);//模板匹配修改文件名，输入模板
    void addRename(const QString&);//在文件名前加一些字符；
private:

    QDir m_Dir;
};

#endif // FILECONTROL_H
