#include "AnimationLine.h"

AnimationLine::AnimationLine(QObject* parent, QGraphicsScene* lscene,
	QPen lpen, Point<long> lp1, Point<long> lp2) : QObject(parent) {
	scene = lscene;
	pen = lpen;
	p1 = lp1;
	p2 = lp2;
	pColor = pen.color();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(fadeLine()));
	timer->start(15);

	line = scene->addLine(p1.x, p1.y, p2.x, p2.y, pen);
}
AnimationLine::AnimationLine(const AnimationLine & A) {

	scene = A.scene;
	pen = A.pen;
	p1 = A.p1;
	p2 = A.p2;
	pColor = A.pColor;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(fadeLine()));
	timer->start(15);
	line = A.line;
}

int AnimationLine::reduceAlpha()
{
	int newAlpha = pColor.alpha() - 5;

	int newWidth = 0;
	if (newAlpha < 0) {
		newAlpha = 0;
		//newWidth = 0;
	}
	else {
		newWidth = pen.width() - 2;
	}
	if (newAlpha < 70) {
		newAlpha += 3;
	}
	if (newWidth < 50) {
		newWidth += 0.6;
	}

	pColor.setAlpha(newAlpha);
	pen.setColor(pColor);
	pen.setWidth(newWidth);
	return newAlpha;
}

void AnimationLine::fadeLine()
{
	if (reduceAlpha() == 0) {
		timer->stop();
	}
	line->setPen(pen);
}

