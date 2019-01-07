#ifndef GESUTURE_TOUCH_CALLBACK_H
#define GESUTURE_TOUCH_CALLBACK_H

#include "Containers.h"
#include "CoordinateMapper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include "Keyboard.h"

#include <vector>

extern GestureKey touch_trace;

class GestureTouchCallback : public TouchCallback
{
public:
    void SetTouchpadRect(Rect<long> touchpadRect);
    void SetSmoothingWeight(int weight);
    void SetSendClick(bool sendClick);

private:
    void OnTouchStarted(Point<long> touchPt) override;
    void OnTouchMoved(Point<long> touchPt) override;
    void OnTouchEnded() override;

	Point<long> TouchToScreen(Point<long> touchPt);

    CoordinateMapper m_coordMapper;
    TouchProcessor m_touchProcessor;
    bool m_sendClick = false;
};

#endif
