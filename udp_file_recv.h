#ifndef UDP_FILE_RECV_H
#define UDP_FILE_RECV_H
#include <QReadWriteLock>
#include <QQueue>
#include <QFile>
#include <QDir>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QScrollBar>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include <QUdpSocket>
#include <QFile>
#include <QNetworkDatagram>
#include "udt_src/udt.h"

#ifndef WIN32
   #include <unistd.h>
   #include <cstdlib>
   #include <cstring>
   #include <netdb.h>
#else
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #include <wspiapi.h>
#endif
#include <iostream>

using namespace std;

#ifndef WIN32
void* recvdata(void*);
#else
DWORD WINAPI recvdata(LPVOID);
#endif

class UDP_FILE_RECV_THREAD:public QObject
{
    Q_OBJECT
public:
    UDP_FILE_RECV_THREAD();
    ~UDP_FILE_RECV_THREAD();
public slots:
    void run(QString ip,int port,QString save_path);
    //关闭文件
    void close_file();
    void WriteLog(QString text);
signals:
    void LogSend(QString text);
    //参数1: 当前接收的文件名称 参数2: 当前已经接收的字节  参数3:总字节数 参数4:接收速度
    void ss_FileRecvState(QString,qint64,qint64,double speed);
    //发送完成通知,参数: 丢包率
    void ss_RecvComplete(double FailureRate);
private:
    bool file_recv_state=0;
    qint64 recv_cnt=0;  //接收的字节数量

    qint64 recv_file_size=0; //接收文件的总大小
    QString recv_file_name; //接收文件的名称

    QFile *recv_file_p=nullptr;

    QTimer *update_time=nullptr;

    qint64 current_ms_time=0;  //当前时间
    qint64 old_ms_time=0;  //上次时间
    qint64 rx_byte=0; //计算接收速度
    double speed_M_SEC=10.0; //速度
    bool Start_Recv_flag=0; //开始启动接收的标志

    UDTSOCKET serv;
};


//队列里最大存放的数据
#define QUEUE_DATA_CNT 1024*1024

class StringDataQueue
{
private:
    QReadWriteLock lock; //读写锁
    QQueue<QString> queue; //缓存数据的队列
public:
    StringDataQueue()
    {
        queue.clear();
    }

    //向队列里插入一条数据
    void write_queue(QString data)
    {
        lock.lockForWrite();
        queue.enqueue(data);
        if(queue.size()>QUEUE_DATA_CNT) //最大缓存数据
        {
            queue.clear();
        }
        lock.unlock();
    }

    //返回队列里的一条数据
    QString read_queue()
    {
        QString data="";
        lock.lockForWrite();
        //判断队列是否为空,有数据才取
        if(queue.isEmpty()==false)
        {
            data=queue.dequeue();
        }
        lock.unlock();
        return data;
    }

    //返回队列里剩余的数据数量
    int get_queue1_cnt()
    {
        int data=-1;
        lock.lockForWrite();
        data=queue.count();
        lock.unlock();
        return data;
    }

    //清除队列里的数据
    int clear_queue()
    {
        int data=-1;
        lock.lockForWrite();
        queue.clear();
        lock.unlock();
        return data;
    }
};
extern class StringDataQueue log_queue;
#endif // UDP_FILE_RECV_H

