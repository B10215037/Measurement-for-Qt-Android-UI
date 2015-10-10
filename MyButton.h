#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QAbstractButton>

class MyButton : public QAbstractButton
{
	Q_OBJECT
public:
	explicit MyButton(int id = -1, QWidget *parent = 0);

protected:
	int id;
	void paintEvent(QPaintEvent *evt);

signals:
	void clicked(int);

public slots:
	void sendId();
};

#endif // MYBUTTON_H
