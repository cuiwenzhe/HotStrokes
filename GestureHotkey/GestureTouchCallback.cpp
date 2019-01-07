#include "GestureTouchCallback.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include "ExternContainer.h"
#include "InputHelper.h"
#include <iostream>

//#define SHOWCURSOR

//Dictionary dict("wordlist.txt");
void GestureTouchCallback::SetTouchpadRect(Rect<long> touchpadRect)
{
	m_coordMapper.SetTouchpadRect(touchpadRect);
}

void GestureTouchCallback::SetSmoothingWeight(int weight)
{
	m_touchProcessor.SetWeight(weight);
}

void GestureTouchCallback::SetSendClick(bool sendClick)
{
	m_sendClick = sendClick;
}

void GestureTouchCallback::OnTouchStarted(Point<long> touchPt)
{

#ifdef SHOWCURSOR
	std::cout << touchPt;
#endif
	if (interface_handler.getSysKeyStatus() == P_CTRL) {
		interface_handler.setWorkingWindow();
		//interface_handler.windowToCursor();
		interface_handler.showCanvas();
		
		interface_handler.draw_point(touchPt, false);
		touch_trace.push_back(touchPt);
	}
	if (m_sendClick) {
		// SendLeftDown(screenPt);
	}
}

void GestureTouchCallback::OnTouchMoved(Point<long> touchPt)
{
#ifdef SHOWCURSOR
	std::cout << touchPt;
#endif
	if (interface_handler.getSysKeyStatus() == P_CTRL) {
		//ShowCursor(FALSE);
		interface_handler.draw_point(touchPt, true);
		touch_trace.push_back(touchPt);
		SetCursorPos(50000, 50000);
	}
}

void GestureTouchCallback::OnTouchEnded()
{
	if (m_sendClick) {
		// SendLeftUp();
	}

	if (touch_trace.isEmpty() == false) {
		interface_handler.handleTrace(touch_trace);
		touch_trace.clear();
		SetCursorPos(1000, 500);
	}
	ShowCursor(TRUE);
	m_touchProcessor.TouchEnded();
}


Point<long> GestureTouchCallback::TouchToScreen(Point<long> touchPt)
{
	Point<long> avgPt = m_touchProcessor.Update(touchPt);
	Point<long> screenPt = m_coordMapper.TouchToScreenCoords(avgPt);
	return screenPt;
}