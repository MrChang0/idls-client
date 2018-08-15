#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "device.h"
#include "setting.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_online_Button_clicked();

    void on_disconnect_Button_clicked();

    void on_sendsignal_pushButton_clicked();

    void on_refresh_pushButton_clicked();

private:
    void send(const QByteArray&);
	void refresh();

    Ui::MainWindow *ui;
    QTcpSocket client;
    Setting setting;
    Device device;
};

#endif // MAINWINDOW_H
