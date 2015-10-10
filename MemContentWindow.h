#ifndef MEMCONTENTWINDOW_H
#define MEMCONTENTWINDOW_H

#include <QMdiSubWindow>
#include "ScrollArea.h"
#include "Sqlite.h"
#include "ActionBar.h"
#include "MyButton.h"

class MemContentWindow : public QMdiSubWindow
{
	Q_OBJECT
public:
	explicit MemContentWindow(QWidget *parent = 0);
	void setContent(int id);
	void keyPressEvent(QKeyEvent *evt);

signals:
	void turnToInfoWindow(int id, QSqlQuery&);
	void back();

public slots:
	void showInfo(int id);

private:
	int id;
	ActionBar *actionBar;
	ScrollArea *scrollArea;
	QList<QWidget*> contentWidgetGroup;
};

#endif // MEMCONTENTWINDOW_H
