#include "ScriptClient.h"

#include <iostream>

ScriptClient::ScriptClient(QObject *parent, int port, QString script)
	: QObject(parent)
{
	this->script = script;
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(transfer()));
	QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

	socket->connectToHost(QHostAddress::LocalHost, port);
}

ScriptClient::~ScriptClient()
{
	socket->close();
}

void ScriptClient::transfer()
{

	socket->write(script.toUtf8()); //write the data 
	socket->waitForReadyRead(3000);
	QString resp = QString(socket->readAll());
	// we need to write to stdout to get output in our editor console
	std::cout << resp.toStdString() << endl;
	socket->waitForDisconnected();
	socket->close();
	qApp->quit();
}


void ScriptClient::displayError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QTcpSocket::RemoteHostClosedError)
		return;
	std::cout << endl << socket->errorString().toStdString() << endl;
	socket->close();
	qApp->quit();
}