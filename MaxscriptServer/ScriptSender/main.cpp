#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include "ScriptClient.h"

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QCommandLineParser parser;
	QCommandLineOption mxsFileOption(QStringList() << "f" << "mxs-file",
		QCoreApplication::translate("main", "specify a mxs file to send to server."),
		QCoreApplication::translate("main", "mxsfile"));
	parser.addOption(mxsFileOption);

	/*
	QCommandLineOption portOption(QStringList() << "p" << "port",
		QCoreApplication::translate("main", "specify a port on localhost."),
		QCoreApplication::translate("main", "port"));
	parser.addOption(portOption);
	*/

	

	// process options
	parser.process(app);

	QString mxsfile = parser.value(mxsFileOption);
	qInfo() << mxsfile;
	std::cout << mxsfile.toStdString();

	// int port = parser.value(portOption).toInt();

	int port = 9999; // hard code for now, but could be an option
	QFile file(mxsfile);
	QFileInfo mxsfile_info = QFileInfo(file);

	// send just the filename over the wire:
	QString script = mxsfile_info.absoluteFilePath();
	ScriptClient client(&app, port, mxsfile);

	return app.exec();

	/*
	// Do this to Send the whole script file over the wire
	// If it's a python script, we wrap it in a mxs call
	QString file_type = mxsfile_info.suffix();
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	return 1;
	QString script = file.readAll();

	if (file_type == "py")
	{
	script = "python.execute(\"" + script + "\")";
	}

	*/
}
