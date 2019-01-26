/** Thanks to the code from https://github.com/apsun/AbsoluteTouch **/

#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <ostream>
#include <vector>

template <typename T>
struct Rect
{
    T x1;
    T y1;
    T x2;
    T y2;

    Rect() = default;
    Rect(T x1, T y1, T x2, T y2) : x1(x1), y1(y1), x2(x2), y2(y2) { }

    T width()
    {
        return x2 - x1;
    }

    T height()
    {
        return y2 - y1;
    }

    Rect<T> scale(Rect<int> scale)
    {
        Rect<long> ret;
        ret.x1 = x1 + width() * scale.x1 / 100;
        ret.x2 = x1 + width() * scale.x2 / 100;
        ret.y1 = y1 + height() * scale.y1 / 100;
        ret.y2 = y1 + height() * scale.y2 / 100;
        return ret;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream &os, Rect<T> rect)
{
    os << "{X1=" << rect.x1 << ", Y1=" << rect.y1;
    os << ", X2=" << rect.x2 << ", Y2=" << rect.y2 << "}";
    return os;
}

template <typename T>
struct Point
{
    T x;
    T y;

    Point() = default;
    Point(T x, T y) : x(x), y(y) { }
};

template <typename T>
std::ostream & operator<<(std::ostream &os, Point<T> point)
{
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

template <class T>
class Trace {
public:
	Trace() {}
	void push_back(T point) { 
		dots.push_back(point); 
	}
	void clear() { dots.clear(); }
private:
	std::vector<T> dots;
};

#endif
