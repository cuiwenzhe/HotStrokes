/** Thanks to the code from https://github.com/apsun/AbsoluteTouch **/

#include "InitGesture.h"
#include "ExternContainer.h"
DWORD g_mainThreadId = 0;
std::atomic<bool> g_cleanupFinished = false;
TouchpadManager *g_touchpadManager = nullptr;
GestureTouchCallback *g_touchCallback = nullptr;
bool g_touchpadEnabledModified = false;

void CleanUp()
{
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



int InitGesture(int argc, char *argv[])
{
	
	CommandLineArgs args(argc, argv);
	if (!args.ok) {
		return 1;
	}
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
	}
	catch (const TouchpadInitException &e) {
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
		int key = 0;
	
		//
		g_touchpadManager->reinitialize();
		
		if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
		{
			BOOL bCtrl = ::GetKeyState(VK_CONTROL) & 0x8000;
			BOOL bShift = ::GetKeyState(VK_SHIFT) & 0x8000;
			BOOL bAlt = ::GetKeyState(VK_MENU) & 0x8000;
			BOOL bEsc = ::GetKeyState(VK_ESCAPE) & 0x8000;
			std::string msgstr = "";

			if (bCtrl&bAlt&&bShift)
				msgstr = "ctrl+alt+shift+";
			else if (bAlt&&bShift)
				msgstr = "alt+shift+";
			else if (bCtrl&&bAlt)
				msgstr = "ctrl+alt+";
			else if (bCtrl&&bShift)
				msgstr = "ctrl+shift+";
			else if (bCtrl) {
				msgstr = "ctrl+";
			}
			else if (bAlt) {
				msgstr = "alt+";
			}

			else if (bShift) {
				msgstr = "shift+";
			}
			
			
			UINT test = MapVirtualKeyA(msg.wParam, MAPVK_VK_TO_CHAR);
		
			char nChar = test;
		
			if (nChar >= 33 && nChar <= 158) {
				if (nChar >= 'A' && nChar <= 'Z') {
					msgstr.push_back(nChar - 'A' + 'a');			
				}
				else {
					msgstr.push_back(nChar);
				}
				if (msgstr.length() > 1)//make sure it is not an letter input
				{
					std::string letter = "";
					letter.push_back(nChar);
					interface_handler.checkShortcut(msgstr);
				}
			}
		}
	}
	CleanUp();
	g_cleanupFinished = true;
	return 0;

}
