#ifndef GESTURE_INIT
#define GESTURE_INIT
#include "CCoInitialize.h"
#include "CommandLineArgs.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include "GestureTouchCallback.h"
#include <atomic>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

int InitGesture(int argc, char *argv[]);

#endif