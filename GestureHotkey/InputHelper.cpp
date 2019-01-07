#include "InputHelper.h"
#include <Windows.h>

void MoveCursor(Point<long> screenPt)
{
	INPUT input[1];
	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = screenPt.x;
	input[0].mi.dy = screenPt.y;
	input[0].mi.mouseData = 0;
	input[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input[0].mi.time = 0;
	SendInput(1, input, sizeof(INPUT));
}

void SendLeftDown(Point<long> screenPt)
{
	INPUT input[2];
	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = screenPt.x;
	input[0].mi.dy = screenPt.y;
	input[0].mi.mouseData = 0;
	input[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input[0].mi.time = 0;
	input[1].type = INPUT_MOUSE;
	input[1].mi.dx = 0;
	input[1].mi.dy = 0;
	input[1].mi.mouseData = 0;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	input[1].mi.time = 0;
	SendInput(2, input, sizeof(INPUT));
}

void SendLeftUp()
{
	INPUT input[1];
	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = 0;
	input[0].mi.dy = 0;
	input[0].mi.mouseData = 0;
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	input[0].mi.time = 0;
	SendInput(1, input, sizeof(INPUT));
}
