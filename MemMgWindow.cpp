#include "MemMgWindow.h"

MemMgWindow::MemMgWindow(QWidget *parent) : QMdiSubWindow(parent)
{
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(new QVBoxLayout);
	centralWidget->layout()->setMargin(0);
	centralWidget->layout()->setSpacing(0);
	setWidget(centralWidget);

	ActionBar *actionBar = new ActionBar("人員管理");
	actionBar->setStyleSheet(actionBar->styleSheet() + "* {background:#ddd;}"  "QToolButton {background:#ddd;}"
		"QToolButton:hover {border:0; background:#ddd;}" "QToolButton:checked {background:#c4c4c4;}");
	centralWidget->layout()->addWidget(actionBar);

	QAction *add= new QAction(QIcon(":/icons/new"), "new", this);
	//connect(proj, SIGNAL(triggered()), this, SLOT()); //O
	actionBar->addButton(add, 2);

	QAction *del = new QAction(QIcon(":/icons/remove"), "remove", this);
	//connect(mem, SIGNAL(triggered()), this, SLOT()); //O
	actionBar->addButton(del, 3);

	ScrollArea *scrollArea = new ScrollArea;
	centralWidget->layout()->addWidget(scrollArea);

	int rowNum = 0;
	QSqlDatabase db = QSqlDatabase::database("Mdb");
	if(db.isOpen())
	{
		QSqlQuery selectQuery("SELECT * FROM GROUPS;", db);
		while(selectQuery.next())
		{
			QLabel *label1 = new QLabel(selectQuery.value("Name").toString());
			label1->setFont(QFont("Times New Roman", font_em(3)));

			QLabel *label2 = new QLabel(selectQuery.value("Amount").toString().append("人"));
			label2->setFont(QFont("Times New Roman", font_em(3)));
			label2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

			MyButton *group = new MyButton(selectQuery.value(0).toInt());
			group->setLayout(new QHBoxLayout);
			group->layout()->addWidget(label1);
			group->layout()->addWidget(label2);
			group->setFixedHeight(8*em);
			connect(group, SIGNAL(clicked(int)), this, SLOT(showContent(int)));

			QWidget *line = new QWidget;
			line->setMinimumHeight(0.5*em);
			line->setMaximumHeight(0.5*em);
			line->setStyleSheet("* {background:black;}");

			scrollArea->layout->insertWidget(rowNum++, group);
			scrollArea->layout->insertWidget(rowNum++, line);
		}
	}

	scrollArea->widget()->adjustSize();
}

void MemMgWindow::showContent(int id)
{
	emit turnToContentWindow(id);
}
