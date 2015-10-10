#include "ProjMgWindow.h"

ProjMgWindow::ProjMgWindow(QWidget *parent) : QMdiSubWindow(parent)
{
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(new QVBoxLayout);
	centralWidget->layout()->setMargin(0);
	centralWidget->layout()->setSpacing(0);
	setWidget(centralWidget);

	ActionBar *actionBar = new ActionBar("專案管理");
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
		QSqlQuery selectQuery("SELECT * FROM PROJECTS;", db);
		while(selectQuery.next())
		{
			QLabel *label1 = new QLabel;
			if(selectQuery.value("IconPath").toString() != "")
				label1->setPixmap(QPixmap(selectQuery.value("IconPath").toString()));
			else
				label1->setPixmap(QPixmap(":/icons/camera"));
			label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			label1->setFixedWidth(12*em);
			label1->setFixedHeight(12*em);
			label1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			label1->setStyleSheet("* {background:#abc; border-radius:" + QString::number(label1->height() / 2) + "px;}");

			QLabel *label2 = new QLabel(selectQuery.value("Name").toString());
			label2->setFont(QFont("Times New Roman", font_em(3)));

			QLabel *label3 = new QLabel(selectQuery.value("Amount").toString());
			label3->setFont(QFont("Times New Roman", font_em(1)));
			label3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			label3->setFixedWidth(4*em);
			label3->setFixedHeight(4*em);
			label3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			label3->setStyleSheet("* {background:#fc0; border-radius:" + QString::number(label3->height() / 2) + "px;}");

			QWidget *top_right = new QWidget;
			top_right->setLayout(new QHBoxLayout);
			top_right->layout()->setMargin(0);
			top_right->layout()->setSpacing(0);
			top_right->layout()->setContentsMargins(0, 0, em, 0);
			top_right->layout()->addWidget(label2);
			top_right->layout()->addWidget(label3);

			QLabel *label4 = new QLabel(selectQuery.value("Description").toString());
			label4->setFont(QFont("Times New Roman", font_em(2.5)));
			label4->setStyleSheet("* {color:#70BF53;}");

			QWidget *right = new QWidget;
			right->setLayout(new QVBoxLayout);
			right->layout()->setMargin(0);
			right->layout()->setSpacing(0);
			right->layout()->addWidget(top_right);
			right->layout()->addWidget(label4);

			MyButton *group = new MyButton;
			group->setLayout(new QHBoxLayout);
			group->layout()->setMargin(0);
			group->layout()->setSpacing(0);
			group->layout()->addWidget(label1);
			group->layout()->addWidget(right);
			group->setFixedHeight(12*em);
//			connect(group, SIGNAL(clicked()), this, SLOT()); //->

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
