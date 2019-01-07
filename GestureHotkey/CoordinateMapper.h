#ifndef COORDINATE_MAPPER_H
#define COORDINATE_MAPPER_H

#include "Containers.h"

class CoordinateMapper
{
public:
    void SetTouchpadRect(Rect<long> rect);

	Point<long> TouchToScreenCoords(Point<long> touchPoint);

private:
    Point<long> ClampTouchPoint(Point<long> touchPoint);
    Rect<long> m_touchpadRect;
	Rect<long> m_screenRect;
};

#endif
