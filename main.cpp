#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Sqlite db;
	MainWindow w;
	w.show();

	return a.exec();
}
