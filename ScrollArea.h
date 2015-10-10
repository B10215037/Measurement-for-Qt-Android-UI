#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QScroller>

class ScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	explicit ScrollArea(QWidget *parent = 0);

	QVBoxLayout *layout;
};

#endif // SCROLLAREA_H
