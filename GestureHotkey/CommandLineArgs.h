#ifndef COMMAND_LINE_ARGS_H
#define COMMAND_LINE_ARGS_H

#include "Containers.h"

class CommandLineArgs
{
public:
    CommandLineArgs(int argc, char *argv[]);
    bool ok;
    Rect<int> screenRect{ 0, 0, 100, 100 };
    Rect<int> touchpadRect{ 0, 0, 100, 100 };
    bool manageTouchpad = false;
    bool sendClick = false;
    int smoothingWeight = 0;
};

#endif
