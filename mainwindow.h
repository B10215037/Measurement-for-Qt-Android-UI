#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "MemMgWindow.h"
#include "MemContentWindow.h"
#include "MemInfoWindow.h"
#include "ProjMgWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    // pages
	MemMgWindow *mem_mg;
	MemContentWindow *mem_content;
	MemInfoWindow *mem_info;
	ProjMgWindow *proj_mg;

private slots:
	void toMemMgPage();
	void toMemContentPage(int id);
	void toMemInfoPage(int id, QSqlQuery &query);
	void toProjMgPage();
};

#endif // MAINWINDOW_H
