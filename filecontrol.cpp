#include "filecontrol.h"
#include<QFileInfoList>
#include<QListIterator>
#include<QRegularExpression>
#include<QDebug>
#include<QThread>

FileControl::FileControl(QObject *parent) : QObject(parent)
{

}

void FileControl::getPath(const QString &path)
{
    m_Dir.setCurrent(path);
}


void FileControl::rxRename(const QString& pattern)//模板匹配修改文件名，输入模板
{
    qDebug()<<"worker ThreadId"<<QThread::currentThreadId();
    m_Dir.refresh();
    if(!m_Dir.isEmpty())
    {
        QRegularExpression rx(pattern);
        QFileInfoList info = m_Dir.entryInfoList();//获取文件夹信息
        QListIterator<QFileInfo> it(info);
        while(it.hasNext())
        {
            QFileInfo temp = it.next();
            QString desName = temp.fileName().replace(rx,"");//清除固定模式的内容得出目标名字
            QString desPath = temp.absolutePath()+"/"+desName;//拼接目标路径
            QFile tempFile(temp.absoluteFilePath());
            tempFile.rename(desPath);
        }
    }
}
void FileControl::addRename(const QString& addContent)//在文件名前加一些字符
{
    qDebug()<<"worker ThreadId"<<QThread::currentThreadId();
    m_Dir.refresh();
    if(!m_Dir.isEmpty())
    {
        QFileInfoList info = m_Dir.entryInfoList();
        QListIterator<QFileInfo> it(info);
        while(it.hasNext())
        {
            QFileInfo temp = it.next();
            QString desName = addContent+temp.fileName();//名字前添加东西得到目标名字
            QString desPath = temp.absolutePath()+"/"+desName;//拼接目标路径

            QFile tempFile(temp.absoluteFilePath());
            tempFile.rename(desPath);
        }
    }
}
