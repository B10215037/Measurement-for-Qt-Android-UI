#ifndef MEMINFOWINDOW_H
#define MEMINFOWINDOW_H

#include <QMdiSubWindow>
#include "ScrollArea.h"
#include "Sqlite.h"
#include "ActionBar.h"
#include "MyButton.h"

class MemInfoWindow : public QMdiSubWindow
{
	Q_OBJECT
public:
	explicit MemInfoWindow(QWidget *parent = 0);
	void setContent(int memContentId, QSqlQuery &selectQuery);
	void keyPressEvent(QKeyEvent *evt);

signals:
	void back(int);

public slots:

private:
	ScrollArea *scrollArea;
	QList<QWidget*> contentWidgetGroup;
	int id, memContentId;
};

#endif // MEMINFOWINDOW_H
