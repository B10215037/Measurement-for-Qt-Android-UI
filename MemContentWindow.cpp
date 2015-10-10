#include "MemContentWindow.h"

MemContentWindow::MemContentWindow(QWidget *parent) : QMdiSubWindow(parent), id(-1)
{
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(new QVBoxLayout);
	centralWidget->layout()->setMargin(0);
	centralWidget->layout()->setSpacing(0);
	setWidget(centralWidget);

	actionBar = new ActionBar("");
	actionBar->setStyleSheet(actionBar->styleSheet() + "* {background:#ddd;}"  "QToolButton {background:#ddd;}"
		"QToolButton:hover {border:0; background:#ddd;}" "QToolButton:checked {background:#c4c4c4;}");
	centralWidget->layout()->addWidget(actionBar);

	QAction *add= new QAction(QIcon(":/icons/new"), "new", this);
	//connect(proj, SIGNAL(triggered()), this, SLOT()); //O
	actionBar->addButton(add, 2);

	QAction *del = new QAction(QIcon(":/icons/remove"), "remove", this);
	//connect(mem, SIGNAL(triggered()), this, SLOT()); //O
	actionBar->addButton(del, 3);

	scrollArea = new ScrollArea;
	centralWidget->layout()->addWidget(scrollArea);
}

void MemContentWindow::setContent(int id)
{
	if(this->id == id) return;

	this->id = id;
	QSqlDatabase db = QSqlDatabase::database("Mdb");
	if(db.isOpen())
	{
		QSqlQuery selectQuery("SELECT Name FROM GROUPS WHERE Id=" + QString::number(id) + ";", db);
		selectQuery.first();
		actionBar->setTitle(selectQuery.value(0).toString());

		while(contentWidgetGroup.size() != 0) delete contentWidgetGroup.takeAt(0);

		int rowNum = 0;
		selectQuery.exec("SELECT * FROM PEOPLE WHERE GroupId LIKE '%<" + QString::number(id) + ">%';");
		while(selectQuery.next())
		{
			QLabel *label1 = new QLabel(selectQuery.value("Name").toString());
			label1->setFont(QFont("Times New Roman", font_em(3)));
			contentWidgetGroup.append(label1);

			MyButton *group = new MyButton(selectQuery.value("Id").toInt());
			group->setLayout(new QHBoxLayout);
			group->layout()->addWidget(label1);
			group->setFixedHeight(8*em);
			connect(group, SIGNAL(clicked(int)), this, SLOT(showInfo(int)));
			contentWidgetGroup.append(group);

			QWidget *line = new QWidget;
			line->setMinimumHeight(0.5*em);
			line->setMaximumHeight(0.5*em);
			line->setStyleSheet("* {background:black;}");
			contentWidgetGroup.append(line);

			scrollArea->layout->insertWidget(rowNum++, group);
			scrollArea->layout->insertWidget(rowNum++, line);
		}

		scrollArea->widget()->adjustSize();
	}
}

void MemContentWindow::showInfo(int id)
{
	QSqlDatabase db = QSqlDatabase::database("Mdb");
	QSqlQuery selectQuery("SELECT * FROM PEOPLE WHERE Id=" + QString::number(id) + ";", db);

	if(db.isOpen())
		emit turnToInfoWindow(this->id, selectQuery);
}

void MemContentWindow::keyPressEvent(QKeyEvent *evt)
{
	if(evt->key() == Qt::Key_Back) emit back();
}
