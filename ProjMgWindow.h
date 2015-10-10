#ifndef PROJMGWINDOW_H
#define PROJMGWINDOW_H

#include <QMdiSubWindow>
#include "ScrollArea.h"
#include "Sqlite.h"
#include "ActionBar.h"
#include "MyButton.h"

class ProjMgWindow : public QMdiSubWindow
{
	Q_OBJECT
public:
	explicit ProjMgWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // PROJMGWINDOW_H
