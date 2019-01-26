/** Thanks to the code from https://github.com/apsun/AbsoluteTouch **/

#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include "Containers.h"

void MoveCursor(Point<long> screenPt);
void SendLeftDown(Point<long> screenPt);
void SendLeftUp();

#endif
