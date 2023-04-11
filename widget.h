#ifndef WIDGET_H
#define WIDGET_H

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
#include "udp_file_recv.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

//日志保存目录
#define LOG_SAVE_DIR "log"
//文件保存目录
#define FILE_SAVE_DIR "file"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    /*页面样式表初始化*/
    void SetStyle(const QString &qssFile);

    //初始化配置
    void InitConfig();

    //加载配置文件
    void Load_Config();
    //保存配置文件
    void Save_Config();
    //创建日志文件
    void CreateLogFile();
    //删除指定目录下的文件
    void del_dir_all_file();
    //删除指定目录下的日志文件
    void del_dir_all_log_file();
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void ss_run_udp_thread(QString ip,int port,QString save_path);
public slots:
    //日志显示
    void Log_Text_Display(QString text);

     void slots_FileRecvState(QString, qint64, qint64, double);

     //发送完成通知,参数: 丢包率
     void slots_RecvComplete(double FailureRate);
private slots:

    void old_file_del_timer_update();

    void log_save_timer_update();

    void current_timer_update();

    void on_pushButton_select_log_file_path_clicked();

    void on_pushButton_select_rx_file_path_clicked();

    void on_pushButton_start_udp_clicked();

    void on_pushButton_save_log_clicked();

    void on_spinBox_log_save_time_valueChanged(int arg1);

    void on_spinBox_file_del_time_valueChanged(int arg1);

    void on_pushButton_del_all_clicked();

    void on_pushButton_del_all_log_clicked();

private:
    Ui::Widget *ui;

    QTimer current_timer; //当前时间
    QTimer log_save_timer; //日志自动保存
    QTimer old_file_del_timer; //旧文件自动删除时间
    QFile *log_file=nullptr;
    QTextStream *log_out_stream=nullptr;

    UDP_FILE_RECV_THREAD udp_file_recv_class;
    QThread udp_file_recv_thread;
};
#endif // WIDGET_H
