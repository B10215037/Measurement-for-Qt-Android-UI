#ifndef MEMMGWINDOW_H
#define MEMMGWINDOW_H

#include <QMdiSubWindow>
#include "ScrollArea.h"
#include "Sqlite.h"
#include "ActionBar.h"
#include "MyButton.h"

class MemMgWindow : public QMdiSubWindow
{
	Q_OBJECT
public:
	explicit MemMgWindow(QWidget *parent = 0);

signals:
	void turnToContentWindow(int);

public slots:
	void showContent(int id);
};

#endif // MEMMGWINDOW_H
