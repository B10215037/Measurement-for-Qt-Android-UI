#include "ActionBar.h"

ActionBar::ActionBar(const QIcon &icon, QWidget *parent) : QWidget(parent)
{
	set();
	appIcon->setIcon(icon);
}

ActionBar::ActionBar(const QString &title, QWidget *parent) : QWidget(parent)
{
	set();
	appIcon->setObjectName("appIcon");
	setStyleSheet(styleSheet() + "QToolButton#appIcon {width:" + Qstr_em(9) + ";}");
	appIcon->setText(title);
	appIcon->setFont(QFont("Times New Roman", font_em(1)));
}

ActionBar::ActionBar(const QString &title, const QIcon &icon, QWidget *parent) : QWidget(parent)
{
	set();
	appIcon->setIcon(icon);
	appIcon->setObjectName("appIcon");
	setStyleSheet(styleSheet() + "QToolButton#appIcon {width:" + Qstr_em(9) + ";}");
	appIcon->setText(title);
	appIcon->setFont(QFont("Times New Roman", font_em(1)));
}

void ActionBar::setTitle(const QString &title)
{
	appIcon->setText(title);
}

void ActionBar::set()
{
	setStyleSheet(
		"* {background:#FB8521;}"
		"QToolButton {width:" + Qstr_em(6) + "; height:" + Qstr_em(4) + "; border:0; background:#FB8521;}"
		"QToolButton:hover {border:0; background:#FB8521;}"
		"QToolButton:checked {background:#E26C08;}"
		"QToolButton QMenu {margin:0; padding:0;}"
		"QToolButton QMenu::item {width:" + Qstr_em(6) + "; height:" + Qstr_em(3) + "; "
			"padding:" + Qstr_em(0.3) + " " + Qstr_em(1.5) + " " + Qstr_em(0.3) + " " + Qstr_em(1.5) + ";"
			"border:1px solid transparent; border-bottom-color:black;}"
		"QToolButton QMenu::item:selected {background:darkgray;}"
		"QToolButton::menu-indicator {image:none;}"
	);

	buttonGroup = new QButtonGroup(this);
	buttonGroup->setExclusive(true);

	layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSizeConstraint(QLayout::SetNoConstraint);
	layout->addStretch();

	appIcon = new QToolButton;

	appIcon->setAutoRaise(false);
	appIcon->setFocusPolicy(Qt::NoFocus);
	appIcon->setMenu(NULL);
	layout->insertWidget(0, appIcon);

	menuButton = new QToolButton;
	menuButton->setIcon(QIcon(":/icons/overflow"));
	menuButton->setAutoRaise(true);
	menuButton->setFocusPolicy(Qt::NoFocus);
	menuButton->setPopupMode(QToolButton::InstantPopup);
	layout->addWidget(menuButton);

	menu = new QMenu(menuButton);
	menu->setStyle(&menustyle);
	menuButton->setMenu(menu);
}

void ActionBar::resizeEvent(QResizeEvent *evt)
{
	int oldWidth = evt->oldSize().width();
	int newWidth = evt->size().width();

	if(oldWidth != newWidth)
		adjustContent();
}

void ActionBar::paintEvent(QPaintEvent *evt)
{
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	if(menu->isEmpty())
		menuButton->setVisible(false);
}

void ActionBar::adjustContent()
{
	menu->repaint();
	appIcon->setIconSize(QSize(3 * em, 3 * em));
	menuButton->setIconSize(QSize(3 * em, 3 * em));
	QList<QAbstractButton*> buttons = buttonGroup->buttons();

	for(int i=0; i<buttonActions.size(); ++i)
	{
		QToolButton *btn = (QToolButton*) buttons.at(i);
		btn->setIconSize(QSize(3 * em, 3 * em));
	}
}

void ActionBar::addMenuItem(QAction *action)
{
	QWidget::addAction(action);

	menu->addAction(action);
	if(!menu->isEmpty())
		menuButton->setMenu(menu);
}

void ActionBar::removeMenuItem(QAction *action)
{
	QWidget::removeAction(action);

	menu->removeAction(action);
	if(menu->isEmpty())
		menuButton->setMenu(NULL);
}

void ActionBar::addButton(QAction *action, int position, bool checkable)
{
	if(position < 0)
		position = buttonActions.size();

	buttonActions.insert(position, action);
	QToolButton *btn = new QToolButton;
	btn->setText(action->text());
	btn->setToolTip(action->toolTip());
	btn->setIcon(action->icon());
	btn->setFont(action->font());
	btn->setEnabled(action->isEnabled());
	btn->setFocusPolicy(Qt::NoFocus);
	btn->setAutoRaise(true);
	btn->setCheckable(checkable);
	connect(btn, SIGNAL(clicked()), action, SLOT(trigger()));
	buttonGroup->addButton(btn);
	layout->insertWidget(position+2, btn);
}

void ActionBar::removeButton(QAction *action)
{
	QToolButton *btn = NULL;
	QList<QAbstractButton*> buttons = buttonGroup->buttons();
	for(int i=0; i<buttonActions.size(); ++i)
	{
		if(buttonActions.at(i) == action)
		{
			btn = (QToolButton*) buttons.at(i);
			break;
		}
	}

	if(btn)
	{
		layout->removeWidget(btn);
		buttonGroup->removeButton(btn);
		delete btn;
		buttonActions.removeOne(action);
	}
}
