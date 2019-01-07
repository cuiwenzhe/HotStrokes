#include "TouchpadManager.h"
#include <cassert>

#define ASSERT_OK(x) do { \
    if ((x) != SYN_OK)    \
        assert(false);    \
} while (0)

TouchpadManager::TouchpadManager()
{
    if (CoCreateInstance(__uuidof(SynAPI), nullptr, CLSCTX_INPROC_SERVER, __uuidof(ISynAPI), (void **)&m_api) != S_OK)
        throw TouchpadInitException("Could not create SynAPI instance");
    if (m_api->Initialize() != SYN_OK) {
        m_api->Release();
        m_api = nullptr;
        throw TouchpadInitException("Could not initialize SynAPI (missing kernel drivers?)");
    }
    long handle = -1;
    if (m_api->FindDevice(SE_ConnectionAny, SE_DeviceTouchPad, &handle) != SYN_OK) {
        m_api->Release();
        m_api = nullptr;
        throw TouchpadInitException("Could not find any touchpad devices");
    }
    ASSERT_OK(m_api->CreateDevice(handle, &m_device));
    ASSERT_OK(m_device->CreatePacket(&m_packet));
    ASSERT_OK(m_device->GetProperty(SP_XLoSensor, &m_bounds.x1));
    ASSERT_OK(m_device->GetProperty(SP_XHiSensor, &m_bounds.x2));
    ASSERT_OK(m_device->GetProperty(SP_YLoSensor, &m_bounds.y1));
    ASSERT_OK(m_device->GetProperty(SP_YHiSensor, &m_bounds.y2));
}

bool TouchpadManager::Acquire()
{
    if (m_acquired)
        return true;
    if (m_device->Acquire(0) != SYN_OK)
        return false;
    m_acquired = true;
    return true;
}

void TouchpadManager::Unacquire()
{
    if (!m_acquired)
        return;
    ASSERT_OK(m_device->Unacquire());
    m_acquired = false;
}

void TouchpadManager::SetTouchCallback(TouchCallback *callback)
{
    if (callback != nullptr && m_callback == nullptr) {
        ASSERT_OK(m_device->SetSynchronousNotification(this));
    } else if (callback == nullptr && m_callback != nullptr) {
        ASSERT_OK(m_device->SetSynchronousNotification(nullptr));
    }
    m_callback = callback;
}

bool TouchpadManager::IsTouchpadEnabled()
{
    HRESULT out;
    ASSERT_OK(m_device->GetProperty(SP_DisableState, &out));
    return (out == SYN_FALSE);
}

void TouchpadManager::SetTouchpadEnabled(bool enabled)
{
    ASSERT_OK(m_device->SetProperty(SP_DisableState, enabled ? SYN_FALSE : SYN_TRUE));
}

Rect<long> TouchpadManager::GetTouchpadRect()
{
    long minX, maxX, minY, maxY;
    ASSERT_OK(m_device->GetProperty(SP_XLoBorder, &minX));
    ASSERT_OK(m_device->GetProperty(SP_XHiBorder, &maxX));
    ASSERT_OK(m_device->GetProperty(SP_YLoBorder, &minY));
    ASSERT_OK(m_device->GetProperty(SP_YHiBorder, &maxY));
    Point<long> topLeft = NormalizeCoordinates(minX, maxY);
    Point<long> bottomRight = NormalizeCoordinates(maxX, minY);
    return Rect<long>(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

Point<long> TouchpadManager::NormalizeCoordinates(long x, long y)
{
    long nx = x - m_bounds.x1;
    long ny = m_bounds.y2 - y;
    return Point<long>(nx, ny);
}

HRESULT STDMETHODCALLTYPE TouchpadManager::OnSynDevicePacket(long seqNum)
{
    HRESULT res = m_device->LoadPacket(m_packet);
    if (res != SYN_OK && res != SYNE_SEQUENCE)
        return res;
    if (m_callback == nullptr)
        return SYN_OK;
    long fingerState;
    m_packet->GetProperty(SP_FingerState, &fingerState);
    bool touching = (fingerState & SF_FingerPresent) != 0;
    if (touching) {
        long x, y;
        Point<long> point;
        m_packet->GetProperty(SP_XRaw, &x);
        m_packet->GetProperty(SP_YRaw, &y);
        point = NormalizeCoordinates(x, y);
        if (m_touching) {
            m_callback->OnTouchMoved(point);
        } else {
            m_callback->OnTouchStarted(point);
            m_touching = true;
        }
    } else if (m_touching) {
        m_callback->OnTouchEnded();
        m_touching = false;
    }
    return SYN_OK;
}

TouchpadManager::~TouchpadManager()
{
    SetTouchCallback(nullptr);
    Unacquire();
    m_packet->Release();
    m_device->Release();
    m_api->Release();
}
