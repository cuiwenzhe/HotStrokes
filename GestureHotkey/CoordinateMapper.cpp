#include "CoordinateMapper.h"

void CoordinateMapper::SetTouchpadRect(Rect<long> touchRect)
{
    m_touchpadRect = touchRect;
}
Point<long> CoordinateMapper::TouchToScreenCoords(Point<long> touchPoint)
{
	Point<long> clampedTouchPoint = ClampTouchPoint(touchPoint);
	long tpWidth = m_touchpadRect.width();
	long tpHeight = m_touchpadRect.height();
	long scWidth = m_screenRect.width();
	long scHeight = m_screenRect.height();
	long tpDeltaX = clampedTouchPoint.x - m_touchpadRect.x1;
	long tpDeltaY = clampedTouchPoint.y - m_touchpadRect.y1;
	long scDeltaX = tpDeltaX * scWidth / tpWidth;
	long scDeltaY = tpDeltaY * scHeight / tpHeight;
	long screenX = m_screenRect.x1 + scDeltaX;
	long screenY = m_screenRect.y1 + scDeltaY;
	return Point<long>(screenX, screenY);
}

Point<long> CoordinateMapper::ClampTouchPoint(Point<long> touchPoint)
{
    if (touchPoint.x < m_touchpadRect.x1)
        touchPoint.x = m_touchpadRect.x1;
    if (touchPoint.x > m_touchpadRect.x2)
        touchPoint.x = m_touchpadRect.x2;
    if (touchPoint.y < m_touchpadRect.y1)
        touchPoint.y = m_touchpadRect.y1;
    if (touchPoint.y > m_touchpadRect.y2)
        touchPoint.y = m_touchpadRect.y2;
    return touchPoint;
}
