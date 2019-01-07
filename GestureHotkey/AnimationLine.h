#pragma once
#include "Containers.h"
#include <QtWidgets/QMainWindow>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QObject> 

class AnimationLine : public QObject
{
	Q_OBJECT
public:
	AnimationLine(const AnimationLine & A);
	AnimationLine(QObject* parent,
		QGraphicsScene* lscene, QPen lpen, Point<long> lp1, Point<long> lp2);
	int reduceAlpha();
	public slots :
	void fadeLine();
private:
	QGraphicsScene * scene;
	QPen pen;
	Point<long> p1;
	Point<long> p2;
	int alpha = 0xff;
	QColor pColor;
	QTimer *timer;
	QGraphicsLineItem* line;
};
