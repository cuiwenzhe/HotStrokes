#ifndef C_CO_INITIALIZE
#define C_CO_INITIALIZE

#include <Windows.h>

class CCoInitialize
{
public:
    CCoInitialize() : m_hr(CoInitialize(nullptr)) { }
    ~CCoInitialize() { if (SUCCEEDED(m_hr)) CoUninitialize(); }

private:
    HRESULT m_hr;
};


#endif
