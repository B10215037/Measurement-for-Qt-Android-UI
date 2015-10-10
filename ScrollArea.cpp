#include "ScrollArea.h"

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
	QWidget *widget = new QWidget;
	setWidget(widget);
	layout = new QVBoxLayout(widget);
	layout->addStretch();
	setWidgetResizable(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QScroller::scroller(this)->grabGesture(this, QScroller::LeftMouseButtonGesture);
}
