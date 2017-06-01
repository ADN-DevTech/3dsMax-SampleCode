#include "Server_Rollup_Wrapper.h"
#include "maxscript\maxscript.h"

Server_Rollup_Wrapper::Server_Rollup_Wrapper(QWidget *parent)
	: QWidget(/*parent*/), 
	ui(new Ui::server_rollup)
{
	ui->setupUi(this);
}

Server_Rollup_Wrapper::~Server_Rollup_Wrapper()
{
	delete ui;
}

void Server_Rollup_Wrapper::Server_Rollup_Wrapper::on_button_start_toggled(bool tog)
{
	if (tog)
	{
		ui->text_status->setPlainText("Server Started");
		tcpServer.listen(QHostAddress::LocalHost, 9999);
		ui->text_status->appendPlainText(tr("Listening on port: %1").arg(tcpServer.serverPort()));
		connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	}

	else
	{
		ui->text_status->setPlainText("Server Stopped");
		tcpServer.close();
		disconnect(&tcpServer, 0, 0, 0);
	}

}

void Server_Rollup_Wrapper::acceptConnection()
{
	tcpServerConnection = tcpServer.nextPendingConnection();
	connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(readData()));
	ui->text_status->appendPlainText("Accepted Connection");
}


void Server_Rollup_Wrapper::readData()
{
	QString res = QString(tcpServerConnection->readAll());

	// for testing:
	// this->ui->text_status->appendPlainText(res);

	FPValue result;
	const wchar_t* buffer;
	buffer = res.toStdWString().c_str();
	TCHAR fileExension[MAX_PATH];
	SplitFilename(buffer, NULL, NULL, fileExension);
	bool success;
	QString result_str = "";
	TSTR script;
	// Are we running a python script?
	if (_tcscmp(fileExension, _T(".py")) == 0 || _tcscmp(fileExension, _T(".pyw")) == 0)
	{
		script.printf(_T("clearListener(); python.executeFile(@\"%s\")"), buffer);
	}
	else // assume we're a mxs script:
	{
		script.printf(_T("clearListener(); filein @\"%s\" quiet:false"), buffer);
	}

	// Execute the script and check for success 
	success = ExecuteMAXScriptScript(script, false, &result);

	// if we failed, let's send back the errors from the listener
	if (!success)
	{
		// try to get the listener output:
		TSTR mxs_script("setListenerSel #(0,-1); ListenerText=getListenerSelText(); setListenerSel #(-1,-1); ListenerText");
		ExecuteMAXScriptScript(mxs_script, true, &result);

		if (result.type && result.type == TYPE_STRING)
		{
			result_str = QString::fromWCharArray(result.s);
		}

		if (result.type && result.type == TYPE_TSTR)
		{
			WStr s = result.tstr->ToWStr();
			result_str = QString::fromWCharArray(s);
		}
	}

	QString success_str = success ? "Succeeded" : "Failed";
	QString success_msg = QString("Result: " + success_str + "\r\n" + result_str + "\r\n");
	tcpServerConnection->write(success_msg.toLocal8Bit());
	tcpServerConnection->flush();
	tcpServerConnection->waitForBytesWritten(3000);
	tcpServerConnection->close();
}