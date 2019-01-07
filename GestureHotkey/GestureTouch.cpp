#include "CCoInitialize.h"
#include "CommandLineArgs.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include "GestureTouchCallback.h"
#include "Keyboard.h"
#include "TestGroup.h"
#include <atomic>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>



/*

DWORD g_mainThreadId = 0;
std::atomic<bool> g_cleanupFinished = false;
TouchpadManager *g_touchpadManager = nullptr;
GestureTouchCallback *g_touchCallback = nullptr;
bool g_touchpadEnabledModified = false;

void PrintUsage()
{
    std::cerr << "usage: AbsoluteTouch.exe <args>\n";
    std::cerr << "  -t x1,y1,x2,y2  Set the mapped touchpad region\n";
    std::cerr << "  -s x1,y1,x2,y2  Set the mapped screen region\n";
    std::cerr << "  -w weight       Set the touch smoothing factor\n";
    std::cerr << "  -c              Enable tap to click\n";
    std::cerr << "  -m              Enable/disable the touchpad on start/exit\n";
    std::cerr << std::flush;
}

void CleanUp()
{
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Exiting..." << std::endl;
    if (g_touchpadManager != nullptr) {
        if (g_touchpadEnabledModified) {
            g_touchpadManager->SetTouchpadEnabled(false);
            g_touchpadEnabledModified = false;
            std::cout << "Disabled touchpad" << std::endl;
        }

        g_touchpadManager->SetTouchCallback(nullptr);
        std::cout << "Unregistered touch callback" << std::endl;

        g_touchpadManager->Unacquire();
        std::cout << "Released exclusive touchpad access" << std::endl;

        delete g_touchpadManager;
        g_touchpadManager = nullptr;
        std::cout << "Uninitialized touchpad manager" << std::endl;
    }

    if (g_touchCallback != nullptr) {
        delete g_touchCallback;
        g_touchCallback = nullptr;
    }
}

BOOL WINAPI OnConsoleSignal(DWORD signal)
{
    switch (signal) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
        // Force main thread to break out of message loop
        PostThreadMessage(g_mainThreadId, WM_QUIT, 0, 0);
        // Wait for main thread to clean up
        while (!g_cleanupFinished);
        break;
    }
    return FALSE;
}

int main(int argc, char *argv[])
{
    CommandLineArgs args(argc, argv);
    if (!args.ok) {
        PrintUsage();
        return 1;
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Starting..." << std::endl;

    // Initialize COM
    CCoInitialize init;

    // Set cleanup handler
    g_mainThreadId = GetCurrentThreadId();
    if (!SetConsoleCtrlHandler(OnConsoleSignal, TRUE)) {
        std::cerr << "Error: failed to register console control handler" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Registered console control handler" << std::endl;

    // Initialize touchpad manager
    try {
        g_touchpadManager = new TouchpadManager();
    } catch (const TouchpadInitException &e) {
        std::cerr << "Error: could not initialize touchpad manager" << std::endl;
        std::cerr << e.what() << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Initialized touchpad manager" << std::endl;

    // Acquire exclusive touchpad access
    if (!g_touchpadManager->Acquire()) {
        std::cerr << "Error: could not acquire exclusive touchpad access" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Acquired exclusive touchpad access" << std::endl;

    // Register touchpad touch callback
    g_touchCallback = new GestureTouchCallback();
    g_touchCallback->SetTouchpadRect(g_touchpadManager->GetTouchpadRect().scale(args.touchpadRect));
    g_touchCallback->SetSmoothingWeight(args.smoothingWeight);
    g_touchCallback->SetSendClick(args.sendClick);
    g_touchpadManager->SetTouchCallback(g_touchCallback);
    std::cout << "Registered touch listener" << std::endl;

    // Enable touchpad if option was specified
    if (args.manageTouchpad && !g_touchpadManager->IsTouchpadEnabled()) {
        g_touchpadManager->SetTouchpadEnabled(true);
        g_touchpadEnabledModified = true;
        std::cout << "Enabled touchpad" << std::endl;
    }

    // Main message loop
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CleanUp();
    g_cleanupFinished = true;


    return 0;
}
*/