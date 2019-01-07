#include "TouchProcessor.h"

void TouchProcessor::SetWeight(int weight)
{
    m_weight = weight;
}

void TouchProcessor::TouchEnded()
{
    m_touching = false;
}

Point<long> TouchProcessor::Update(Point<long> rawPoint)
{
    if (m_weight == 0 || !m_touching) {
        m_average = rawPoint;
        m_touching = true;
    } else {
        m_average.x = ((100 - m_weight) * rawPoint.x + m_weight * m_average.x) / 100;
        m_average.y = ((100 - m_weight) * rawPoint.y + m_weight * m_average.y) / 100;
    }
    return m_average;
}
