#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include "menustyle.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QMenu>
#include <QResizeEvent>
#include <QPainter>
#include <QLabel>

#define androidCompiler true
#define smallerScreen false
#define fontScale 1.7
#define myWppmm 3.95942
#define myHppmm 3.95876
#define wppmm ((double) QApplication::desktop()->width() / (double) QApplication::desktop()->widthMM())
#define hppmm ((double) QApplication::desktop()->height() / (double) QApplication::desktop()->heightMM())
#define wratio (myWppmm / wppmm)
#define hratio (myHppmm / hppmm)

#define font_em(x) (androidCompiler ? x * fontMetrics().height() / fontScale :  x * fontMetrics().height())
#define em (fontMetrics().height() * (smallerScreen ? hratio : 1))
#define Qstr_em(x) QString::number(x * em)

class ActionBar : public QWidget
{
	Q_OBJECT
public:
	explicit ActionBar(const QIcon &icon, QWidget *parent = 0);
	explicit ActionBar(const QString &title, QWidget *parent = 0);
	explicit ActionBar(const QString &title, const QIcon &icon, QWidget *parent = 0);

	void addMenuItem(QAction *action);
	void addButton(QAction *action, int position = -1, bool checkable = false);

	void removeMenuItem(QAction *action);
	void removeButton(QAction *action);

	void adjustContent();

	void setTitle(const QString &title);

protected:
	void paintEvent(QPaintEvent *evt);
	void resizeEvent(QResizeEvent *evt);

private:
	void set();

	QHBoxLayout *layout;
	QToolButton *appIcon;
	QToolButton *menuButton;
	QMenu *menu;
	QList<QAction*> buttonActions;
	QButtonGroup *buttonGroup;
	MenuStyle menustyle;
};

#endif // ACTIONBAR_H
