#include "MyButton.h"
#include <QDebug>

MyButton::MyButton(int id, QWidget *parent) : id(id), QAbstractButton(parent)
{
	connect(this, SIGNAL(clicked()), this, SLOT(sendId()));
}

void MyButton::paintEvent(QPaintEvent *evt) {}

void MyButton::sendId()
{
	emit clicked(id);
}
