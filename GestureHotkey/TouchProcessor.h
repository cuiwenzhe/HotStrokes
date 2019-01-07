#ifndef TOUCH_PROCESSOR_H
#define TOUCH_PROCESSOR_H

#include "Containers.h"

class TouchProcessor
{
public:
    void SetWeight(int weight);
    void TouchEnded();
    Point<long> Update(Point<long> rawPoint);

private:
    int m_weight = 0;
    bool m_touching = false;
    Point<long> m_average;
};

#endif
