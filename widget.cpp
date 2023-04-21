#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置标题
    this->setWindowTitle("UDP协议大文件传输: 服务器端");
    //加载界面样式
    SetStyle(":/blue.css");
    //初始化配置
    InitConfig();
    //加载配置文件
    Load_Config();
    //创建日志文件
    CreateLogFile();
}


Widget::~Widget()
{
    delete ui;
}

/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 加载界面样式
*/
void Widget::SetStyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20,7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
    else
    {
        qApp->setStyleSheet("");
    }
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 界面初始化配置
*/
void Widget::InitConfig()
{
    //获取当前程序的路径
    QString app_path=QCoreApplication::applicationDirPath();

    //设置默认日志保存路径
    QString log_save_path=QString("%1/%2").arg(app_path).arg(LOG_SAVE_DIR);
    QDir dir(log_save_path);
    if(!dir.exists())
    {
        qDebug()<<"日志保存目录不存在.创建目录:"<<log_save_path;
        dir.mkdir(log_save_path);
    }
    ui->lineEdit_log_save_path->setText(log_save_path);

    //设置默认的文件保存路径
    QString file_save_path=QString("%1/%2").arg(app_path).arg(FILE_SAVE_DIR);
    QDir dir_file(file_save_path);
    if(!dir_file.exists())
    {
        qDebug()<<"文件保存目录不存在.创建目录:"<<file_save_path;
        dir_file.mkdir(file_save_path);
    }
    ui->lineEdit_recv_file_save_path->setText(file_save_path);

    //设置本机IP地址
    ui->comboBox_ip_addr->clear();
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int i=0;i<list.count();i++)
    {
        QHostAddress addr=list.at(i);
        if(addr.protocol() == QAbstractSocket::IPv4Protocol)
        {
            ui->comboBox_ip_addr->addItem(addr.toString());
        }
    }


    //显示当前时间
    connect(&current_timer, SIGNAL(timeout()), this, SLOT(current_timer_update()));
    current_timer.start(1000);

    //日志自动保存
    connect(&log_save_timer, SIGNAL(timeout()), this, SLOT(log_save_timer_update()));
    log_save_timer.start(ui->spinBox_log_save_time->value()*1000*60);

    //旧文件自动删除时间
    connect(&old_file_del_timer, SIGNAL(timeout()), this, SLOT(old_file_del_timer_update()));
    old_file_del_timer.start(ui->spinBox_file_del_time->value()*1000*60);

    //连接UDP接收启动函数
    connect(this,SIGNAL(ss_run_udp_thread(QString,int,QString)),&udp_file_recv_class,SLOT(run(QString,int,QString)));
    //连接日志发送函数
    connect(&udp_file_recv_class,SIGNAL(LogSend(QString)),this,SLOT(Log_Text_Display(QString)));
    //连接状态信号
    connect(&udp_file_recv_class,SIGNAL(ss_FileRecvState(QString,qint64,qint64,double)),this,SLOT(slots_FileRecvState(QString,qint64,qint64,double)));
    //连接接收完成信号
    connect(&udp_file_recv_class,SIGNAL(ss_RecvComplete(double)),this,SLOT(slots_RecvComplete(double)));

    //将串口工作对象移动到子线程里工作
    udp_file_recv_class.moveToThread(&udp_file_recv_thread);
    //启动线程
    udp_file_recv_thread.start();
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 显示当前时间
*/
void Widget::current_timer_update()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    ui->label_current_time->setText(current_date);

    QString str;
    if(log_queue.get_queue1_cnt()>0)
    {
        str+=log_queue.read_queue()+"\n";
    }
    if(!str.isEmpty())Log_Text_Display(str);
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 选择日志文件存储目录
*/
void Widget::on_pushButton_select_log_file_path_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择目录","C:/",
    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty())
    {
         ui->lineEdit_log_save_path->setText(dir);

         //创建日志文件
         if(log_file)log_file->close();
         if(log_out_stream)delete log_out_stream;
         CreateLogFile();
    }
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 选择接收文件的存储目录
*/
void Widget::on_pushButton_select_rx_file_path_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择目录","C:/",
    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty())
    {
         ui->lineEdit_recv_file_save_path->setText(dir);
    }
}

/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 窗口关闭事件
*/
void Widget::closeEvent(QCloseEvent *event)
{
    udp_file_recv_class.close_file();
    udp_file_recv_thread.quit();
    udp_file_recv_thread.wait();
    //保存日志
    if(log_out_stream)*log_out_stream<<ui->plainTextEdit_log->toPlainText();
    if(log_file)log_file->close();
    if(log_out_stream)delete log_out_stream;
    current_timer.stop();
    Save_Config();
    event->accept(); //接受事件
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能:加载配置文件
*/
void Widget::Load_Config()
{
    //读取配置文件
    QString text;
    text=QCoreApplication::applicationDirPath()+"/"+"config.ini";

    //判断文件是否存在
    if(QFile::exists(text))
    {
        QFile filenew(text);
        filenew.open(QIODevice::ReadOnly);
        QDataStream in(&filenew); // 从文件读取序列化数据

        int val;
        QString str;
        in >> val;
        ui->spinBox_port->setValue(val);

        in >> str;
        QDir log_save(str);
        if(log_save.exists())ui->lineEdit_log_save_path->setText(str);

        in >> str;
        QDir recv_file(str);
        if(recv_file.exists())ui->lineEdit_recv_file_save_path->setText(str);

        in >> val;
        ui->spinBox_file_del_time->setValue(val);

        in >> val;
        ui->spinBox_log_save_time->setValue(val);

        filenew.close();
    }
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 保存配置文件
*/
void Widget::Save_Config()
{
    /*保存数据到文件,方便下次加载*/
    QString text;
    text=QCoreApplication::applicationDirPath()+"/"+"config.ini";
    QFile filesrc(text);
    filesrc.open(QIODevice::WriteOnly);
    QDataStream out(&filesrc);
    out << ui->spinBox_port->value();  //序列化写
    out << ui->lineEdit_log_save_path->text();  //序列化写
    out << ui->lineEdit_recv_file_save_path->text();  //序列化写
    out << ui->spinBox_file_del_time->value();
    out << ui->spinBox_log_save_time->value();
    filesrc.flush();
    filesrc.close();
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 日志显示
*/
void Widget::Log_Text_Display(QString text)
{
    QPlainTextEdit *plainTextEdit_log=ui->plainTextEdit_log;
    //设置光标到文本末尾
    plainTextEdit_log->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
//    //当文本数量超出一定范围就清除
//    if(plainTextEdit_log->toPlainText().size()>1024*4)
//    {
//        plainTextEdit_log->clear();
//    }
    plainTextEdit_log->insertPlainText(text);
    //移动滚动条到底部
    QScrollBar *scrollbar = plainTextEdit_log->verticalScrollBar();
    if(scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 启动UDP服务器
*/
void Widget::on_pushButton_start_udp_clicked()
{
    //启动服务器
    if (ui->pushButton_start_udp->text() == QString("启动UDP服务器"))
    {
        QString ip = ui->comboBox_ip_addr->currentText();
        qint16 port = ui->spinBox_port->value();
        if (ip.isEmpty())return;
        if (port <= 0)return;

        //启动线程
        udp_file_recv_thread.start();
        //开始监听UDP服务器
        emit ss_run_udp_thread(ip, port, ui->lineEdit_recv_file_save_path->text());

        ui->pushButton_start_udp->setText(QString("停止UDP服务器"));
        Log_Text_Display("UDP服务器已启动... \n");

    }
    //停止服务器
    else if (ui->pushButton_start_udp->text()=="停止UDP服务器")
    {
        //退出线程
        udp_file_recv_class.close_file();
        udp_file_recv_thread.quit();
        udp_file_recv_thread.wait();

        ui->pushButton_start_udp->setText(QString("启动UDP服务器"));
        Log_Text_Display("UDP服务器已关闭...\n");
    }
}


/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 清空日志并保存
*/
void Widget::on_pushButton_save_log_clicked()
{
    //保存日志
    if(log_out_stream)*log_out_stream<<ui->plainTextEdit_log->toPlainText();

    //清空日志
    ui->plainTextEdit_log->clear();
}

/*
工程: UDP_Server
日期: 2021-04-22
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 创建日志文件
*/
void Widget::CreateLogFile()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd-hh-mm-ss");

    QString file_path=QString("%1/%2.txt").arg(ui->lineEdit_log_save_path->text()).arg(current_date);

    log_file=new QFile();
    log_file->setFileName(file_path);
    if(log_file->open(QIODevice::ReadWrite|QIODevice::Text)==true)
    {
        log_out_stream=new QTextStream(log_file);
        Log_Text_Display(tr("%1 日志文件创建成功.\n").arg(file_path));
    }
    else
    {
        log_file=nullptr;
        log_out_stream=nullptr;
        Log_Text_Display(tr("%1 日志文件创建失败.\n").arg(file_path));
    }
}


/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 自动清理日志
*/
void Widget::on_spinBox_log_save_time_valueChanged(int arg1)
{
    log_save_timer.start(arg1*1000*60);
}


/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 定时保存日志
*/
void Widget::log_save_timer_update()
{
    //保存日志
    if(log_out_stream)*log_out_stream<<ui->plainTextEdit_log->toPlainText();

    //清空日志
    ui->plainTextEdit_log->clear();
}

/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 接收到的旧文件自动删除时间
*/
void Widget::on_spinBox_file_del_time_valueChanged(int arg1)
{
     old_file_del_timer.start(ui->spinBox_file_del_time->value()*1000*60);
}


/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 旧文件超时自动删除
*/
void Widget::old_file_del_timer_update()
{
    del_dir_all_file();
}

/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 删除指定目录下的全部文件
*/
void Widget::del_dir_all_file()
{
    QString path=ui->lineEdit_recv_file_save_path->text();
    if (path.isEmpty())
        return;

    QDir dir(path);
    if (!dir.exists())
        return;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach(QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            if(fi.dir().remove(fi.fileName()))
            {
                QFileInfo info(fi.fileName());
                Log_Text_Display(QString("已删除:%1\n").arg(fi.fileName()));
            }
        }
    }
}

/*
工程: UDP_Server
日期: 2021-04-25
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 删除全部日志文件
*/
void Widget::del_dir_all_log_file()
{
    QString path=ui->lineEdit_log_save_path->text();
    if (path.isEmpty())
        return;

    QDir dir(path);
    if (!dir.exists())
        return;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach(QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            if(fi.dir().remove(fi.fileName()))
            {
                QFileInfo info(fi.fileName());
                Log_Text_Display(QString("已删除:%1\n").arg(fi.fileName()));
            }
        }
    }
}


/*
工程: UDP_Server
日期: 2021-04-23
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 文件接收状态
*/
void Widget::slots_FileRecvState(QString name,qint64 recv_byte,qint64 total_byte,double speed)
{
    QString text=QString("正在接收:%1,总大小:%2,已接收:%3,速度:%4M/s\n").arg(name).arg(total_byte).arg(recv_byte).arg(speed);
    Log_Text_Display(text);

    if(recv_byte>=total_byte)
    {
        Log_Text_Display(QString("文件接收完毕. 丢包率:0%\n"));
    }
}


/*
工程: UDP_Server
日期: 2021-04-24
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 接收完成.
*/
void Widget::slots_RecvComplete(double FailureRate)
{
    QString rate=QString("文件接收完毕. 丢包率:%1").arg(FailureRate);
    rate+="%\n";
    Log_Text_Display(rate);
}


/*
工程: UDP_Server
日期: 2021-04-24
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 清空接收目录
*/
void Widget::on_pushButton_del_all_clicked()
{
    int value;
    value=QMessageBox::question(this,"询问提示","你正准备删除接收目录下全部文件,确定吗?",
    QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    switch(value)
    {
    case QMessageBox::Yes:
    /*处理代码*/
        //删除接收目录下的所有文件
        del_dir_all_file();
    break;
    case QMessageBox::No:
    /*处理代码*/
    break;
    }
}

/*
工程: UDP_Server
日期: 2021-04-25
作者: Leventure
环境: win10 QT5.12.6 MinGW32
功能: 清空日志保存目录
*/
void Widget::on_pushButton_del_all_log_clicked()
{
    int value;
    value=QMessageBox::question(this,"询问提示","你正准备删除全部日志文件,确定吗?",
    QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    switch(value)
    {
    case QMessageBox::Yes:
    /*处理代码*/
        //删除接收目录下的所有文件
        del_dir_all_log_file();
    break;
    case QMessageBox::No:
    /*处理代码*/
    break;
    }
}

