#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(new QVBoxLayout);
	centralWidget->layout()->setMargin(0);
	centralWidget->layout()->setSpacing(0);
	setCentralWidget(centralWidget);

	ActionBar *tabBar = new ActionBar(QIcon(":/icons/logo"));
	centralWidget->layout()->addWidget(tabBar);

	QAction *proj = new QAction(QIcon(":/icons/project"), "project", this);
	connect(proj, SIGNAL(triggered()), this, SLOT(toProjMgPage()));
	tabBar->addButton(proj, 2, true);

	QAction *mem = new QAction(QIcon(":/icons/member"), "member", this);
	connect(mem, SIGNAL(triggered()), this, SLOT(toMemMgPage()));
	tabBar->addButton(mem, 3, true);

	QMdiArea *mdiArea = new QMdiArea;
	centralWidget->layout()->addWidget(mdiArea);

	mem_mg = new MemMgWindow(mdiArea);
	mem_mg->setAttribute(Qt::WA_DeleteOnClose);
	mem_mg->setWindowFlags (Qt::SubWindow | Qt::FramelessWindowHint);
	mem_mg->hide();
	connect(mem_mg, SIGNAL(turnToContentWindow(int)), this, SLOT(toMemContentPage(int)));

	mem_content = new MemContentWindow(mdiArea);
	mem_content->setAttribute(Qt::WA_DeleteOnClose);
	mem_content->setWindowFlags (Qt::SubWindow | Qt::FramelessWindowHint);
	mem_content->hide();
	connect(mem_content, SIGNAL(turnToInfoWindow(int ,QSqlQuery&)), this, SLOT(toMemInfoPage(int ,QSqlQuery&)));
	connect(mem_content, SIGNAL(back()), this, SLOT(toMemMgPage()));

	mem_info = new MemInfoWindow(mdiArea);
	mem_info->setAttribute(Qt::WA_DeleteOnClose);
	mem_info->setWindowFlags (Qt::SubWindow | Qt::FramelessWindowHint);
	mem_info->hide();
	connect(mem_info, SIGNAL(back(int)), this, SLOT(toMemContentPage(int)));

	proj_mg = new ProjMgWindow(mdiArea);
	proj_mg->setAttribute(Qt::WA_DeleteOnClose);
	proj_mg->setWindowFlags (Qt::SubWindow | Qt::FramelessWindowHint);
	proj_mg->hide();

	toProjMgPage();
}

void MainWindow::toProjMgPage()
{
	proj_mg->showMaximized();
}

void MainWindow::toMemMgPage()
{
	mem_mg->showMaximized();
}

void MainWindow::toMemContentPage(int id)
{
	mem_content->setContent(id);
	mem_content->showMaximized();
}

void MainWindow::toMemInfoPage(int id, QSqlQuery &query)
{
	mem_info->setContent(id, query);
	mem_info->showMaximized();
}
