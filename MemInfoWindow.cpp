#include "MemInfoWindow.h"

MemInfoWindow::MemInfoWindow(QWidget *parent) : QMdiSubWindow(parent), id(-1)
{
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(new QVBoxLayout);
	centralWidget->layout()->setMargin(0);
	centralWidget->layout()->setSpacing(0);
	setWidget(centralWidget);

	ActionBar *actionBar = new ActionBar("");
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

void MemInfoWindow::setContent(int memContentId,QSqlQuery &selectQuery)
{
	selectQuery.next();
	if(selectQuery.value("Id").toInt() == id) return;

	id = selectQuery.value("Id").toInt();
	this->memContentId = memContentId;

	while(contentWidgetGroup.size() != 0) delete contentWidgetGroup.takeAt(0);

	QLabel *label1 = new QLabel;
	if(selectQuery.value("PicturePath").toString() != "")
		label1->setPixmap(QPixmap(selectQuery.value("PicturePath").toString()));
	else
		label1->setPixmap(QPixmap(":/icons/camera"));
	label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	label1->setFixedWidth(48*em);
	label1->setFixedHeight(48*em);
	label1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	contentWidgetGroup.append(label1);

	QWidget *group1_topRight = new QWidget;
	group1_topRight->setLayout(new QHBoxLayout);

	QStringList groupIdList = selectQuery.value("GroupId").toString().split(QRegExp("[<>]"), QString::SkipEmptyParts);
	QSqlDatabase db = QSqlDatabase::database("Mdb");
	for(int i = 0; i < groupIdList.size(); i ++)
	{
		QSqlQuery query("SELECT Name FROM GROUPS WHERE Id=" + groupIdList.value(i) + ";", db);
		query.first();
		QLabel *label2 = new QLabel(query.value("Name").toString());
		label2->setFont(QFont("Times New Roman", font_em(2)));
		label2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		contentWidgetGroup.append(label2);

		group1_topRight->layout()->addWidget(label2);
	}
	contentWidgetGroup.append(group1_topRight);

	QLabel *label3 = new QLabel(selectQuery.value("Name").toString());
	label3->setFont(QFont("Times New Roman", font_em(2)));
	contentWidgetGroup.append(label3);

	QWidget *group1_right = new QWidget;
	group1_right->setLayout(new QVBoxLayout);
	group1_right->layout()->addWidget(group1_topRight);
	group1_right->layout()->addWidget(label3);
	contentWidgetGroup.append(group1_right);

	QWidget *group1 = new QWidget;
	group1->setLayout(new QHBoxLayout);
	group1->layout()->addWidget(label1);
	group1->layout()->addWidget(group1_right);
	group1->setFixedHeight(48*em);
	contentWidgetGroup.append(group1);

	QLabel *label4 = new QLabel("胸寬");
	label4->setFont(QFont("Times New Roman", font_em(2)));
	label4->setFixedWidth(10*em);
	label4->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	label4->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	label4->setStyleSheet("* {background:#0A9EDC}");
	contentWidgetGroup.append(label4);

	QLabel *label4_1 = new QLabel(selectQuery.value("Bust").toString() + "cm");
	label4_1->setFont(QFont("Times New Roman", font_em(2)));
	label4_1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	contentWidgetGroup.append(label4_1);

	QWidget *group2_1 = new QWidget;
	group2_1->setLayout(new QHBoxLayout);
	group2_1->layout()->addWidget(label4);
	group2_1->layout()->addWidget(label4_1);
	contentWidgetGroup.append(group2_1);

	QLabel *label5 = new QLabel("上身長");
	label5->setFont(QFont("Times New Roman", font_em(2)));
	label5->setFixedWidth(10*em);
	label5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	label5->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	label5->setStyleSheet("* {background:#0A9EDC}");
	contentWidgetGroup.append(label5);

	QLabel *label5_1 = new QLabel(selectQuery.value("Length").toString() + "cm");
	label5_1->setFont(QFont("Times New Roman", font_em(2)));
	label5_1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	contentWidgetGroup.append(label5_1);

	QWidget *group2_2 = new QWidget;
	group2_2->setLayout(new QHBoxLayout);
	group2_2->layout()->addWidget(label5);
	group2_2->layout()->addWidget(label5_1);
	contentWidgetGroup.append(group2_2);

	QLabel *label6 = new QLabel("臂長");
	label6->setFont(QFont("Times New Roman", font_em(2)));
	label6->setFixedWidth(10*em);
	label6->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	label6->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	label6->setStyleSheet("* {background:#0A9EDC}");
	contentWidgetGroup.append(label6);

	QLabel *label6_1 = new QLabel(selectQuery.value("SleeveLength").toString() + "cm");
	label6_1->setFont(QFont("Times New Roman", font_em(2)));
	label6_1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	contentWidgetGroup.append(label6_1);

	QWidget *group2_3 = new QWidget;
	group2_3->setLayout(new QHBoxLayout);
	group2_3->layout()->addWidget(label6);
	group2_3->layout()->addWidget(label6_1);
	contentWidgetGroup.append(group2_3);

	QWidget *group2 = new QWidget;
	group2->setLayout(new QVBoxLayout);
	group2->layout()->addWidget(group2_1);
	group2->layout()->addWidget(group2_2);
	group2->layout()->addWidget(group2_3);
	contentWidgetGroup.append(group2);

	QStringList projectIdList = selectQuery.value("ProjectId").toString().split(QRegExp("[<>]"), QString::SkipEmptyParts);
	QLabel *label7 = new QLabel("專案");
	label7->setFont(QFont("Times New Roman", font_em(2)));
	label7->setFixedWidth(10*em);
	label7->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	label7->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	label7->setStyleSheet("* {background:#0A9EDC}");
	contentWidgetGroup.append(label7);

	QWidget *group3 = new QWidget;
	group3->setLayout(new QHBoxLayout);
	group3->layout()->addWidget(label7);

	for(int i = 0; i < projectIdList.size(); i ++)
	{
		selectQuery.exec("SELECT Name FROM PROJECTS WHERE Id=" + projectIdList.value(i) + ";");
		selectQuery.first();
		QLabel *label8 = new QLabel(selectQuery.value("Name").toString());
		label8->setFont(QFont("Times New Roman", font_em(2)));
		label8->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		contentWidgetGroup.append(label8);

		group3->layout()->addWidget(label8);
	}
	contentWidgetGroup.append(group3);

	int rowNum = 0;
	scrollArea->layout->insertWidget(rowNum++, group1);
	scrollArea->layout->insertWidget(rowNum++, group2);
	scrollArea->layout->insertWidget(rowNum++, group3);
	scrollArea->widget()->adjustSize();
}

void MemInfoWindow::keyPressEvent(QKeyEvent *evt)
{
	if(evt->key() == Qt::Key_Back) emit back(memContentId);
}
