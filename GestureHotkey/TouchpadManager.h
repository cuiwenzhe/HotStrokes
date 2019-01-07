#ifndef TOUCHPAD_MANAGER_H
#define TOUCHPAD_MANAGER_H

#include "Containers.h"
#include "Include/SynKit.h"
#include <exception>

class TouchpadInitException : public std::runtime_error
{
public:
    TouchpadInitException(const char *msg) : std::runtime_error(msg) { }
};

class TouchCallback
{
public:
    virtual void OnTouchStarted(Point<long> touchPt) = 0;
    virtual void OnTouchMoved(Point<long> touchPt) = 0;
    virtual void OnTouchEnded() = 0;
};

class TouchpadManager : private _ISynDeviceEvents
{
public:
    TouchpadManager();
    bool Acquire();
    void Unacquire();
    void SetTouchCallback(TouchCallback *callback);
    bool IsTouchpadEnabled();
    void SetTouchpadEnabled(bool enabled);
    Rect<long> GetTouchpadRect();
    ~TouchpadManager();

private:
    Point<long> NormalizeCoordinates(long x, long y);
    HRESULT STDMETHODCALLTYPE OnSynDevicePacket(long seqNum) override;

    ISynAPI *m_api = nullptr;
    ISynDevice *m_device = nullptr;
    ISynPacket *m_packet = nullptr;
    TouchCallback *m_callback = nullptr;
    Rect<long> m_bounds;
    bool m_acquired = false;
    bool m_touching = false;
};

#endif
