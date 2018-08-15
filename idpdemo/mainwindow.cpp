#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QByteArray>

#include "signal.h"
#include "event.h"
#include "client.h"
#include "server.h"
#include "setting.h"

int size_buf(const QByteArray& buf)
{
	return static_cast<int>(buf[0])<<8 | buf[1];
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    setting("./idpdemo.ini"),
    device(setting)
{
    ui->setupUi(this);
    connect(&client,&QTcpSocket::connected,[this](){qDebug()<<"connected";send(Client::online(device));});
    connect(&client,&QTcpSocket::disconnected,[](){qDebug()<<"disconneted";});
    connect(&client, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
         [=](QAbstractSocket::SocketError socketError){ qDebug()<<"error"<<socketError;});

	connect(&client,&QTcpSocket::readyRead,[this]()
	{
		auto buffer = client.read(2);
		auto size = size_buf(buffer);
		buffer = client.read(size);
		send(Server::deal(buffer,device));
        ui->event_lineEdit->setText(device.EventString());
	});
	refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send(const QByteArray &buf){
	const auto length = buf.size() & 0xffff;
    QByteArray data;
    data.resize(2);
    data[0] = length>>8 & 0xff;
    data[1] = length & 0xff;
    data.append(buf);
    client.write(data);
}
 
void MainWindow::refresh()
{
    ui->uuid1_lineEdit->setText(device.getuuid().mid(0,8));
    ui->uuid2_lineEdit->setText(device.getuuid().mid(8,8));
    ui->uuid3_lineEdit->setText(device.getuuid().mid(16,8));
    ui->type_lineEdit->setText(device.gettype());
    ui->name_lineEdit->setText(device.getname());
    ui->descripton_lineEdit->setText(device.getdescription());

    ui->signals_textEdit->setText(setting.signalstrs.join('\n'));
    ui->events_textEdit->setText(setting.eventstrs.join('\n'));
}


void MainWindow::on_online_Button_clicked()
{
	const auto port = ui->port->text().toInt();
	const auto ip = ui->ipaddress->text();
    client.connectToHost(ip,port);
}

void MainWindow::on_disconnect_Button_clicked()
{
    client.disconnectFromHost();
}

void MainWindow::on_sendsignal_pushButton_clicked()
{
    if(ui->siganl_lineEdit->text().isEmpty())
        return;
    auto text = ui->siganl_lineEdit->text();
    send(Client::signal(Signal::Parse(device.getSignalTypes(),text)));
}

void MainWindow::on_refresh_pushButton_clicked()
{

}
