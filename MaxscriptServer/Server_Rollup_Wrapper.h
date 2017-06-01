#pragma once
#include "ui_server_rollup.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui
{
	class server_rollup;

};

class Server_Rollup_Wrapper : public QWidget
{
	Q_OBJECT

public:
	Server_Rollup_Wrapper(QWidget *parent = nullptr);
	~Server_Rollup_Wrapper();

protected slots:
	void on_button_start_toggled(bool tog);
	void acceptConnection();
	void readData();

private:
	Ui::server_rollup* ui;
	QTcpServer tcpServer;
	QTcpSocket *tcpServerConnection;
};
