#pragma once

#include <QObject>
#include <QtNetwork>

class ScriptClient : public QObject
{
	Q_OBJECT

public:
	ScriptClient(QObject *parent, int port, QString script);
	~ScriptClient();

public slots:
	void transfer();
	void displayError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket* socket;
	QString script; // the script text to exectue
};
