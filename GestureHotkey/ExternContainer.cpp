#include "ExternContainer.h"
#include "QTWindows.h"
#include "TestGroup.h"
#include "windows.h"
#include "Appmodel.h"
#include <Psapi.h>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <tlhelp32.h>


//define extern containers
TraceLog tracelog;
GestureKey touch_trace;
Dictionary* dict;
InterfaceHandler interface_handler;

/*************************
*      Exe Functions
*************************/
void InterfaceHandler::handleTrace(GestureKey &trace)
{
	touch_trace.normalize_resample_points(100);
	dict->calculate_words_score(touch_trace);
	WordLog word_log(tracelog, wordstr);
	std::string word = dict->get_first_word();
	double error = dict->get_first_word_error();
	if (error > 0.3) {
		word = "try again";
		current_word = "";
		interface_handler.showText(word,"Fail to identify");
	}
	else {
		current_word = word;
		triggerHotkey(current_word);
		interface_handler.showText(word,
			workingWindow->getHotkeyByCommand(current_word));
	}
}

void InterfaceHandler::checkShortcut(std::string str)
{
	if (pop_window_p->isVisible()) {
		pop_window_p->setHotkey(str);
	}
}

void InterfaceHandler::reInitialTouchpad()
{
	SendMessage(HWND_BROADCAST,9527,NULL,NULL);
	reinitializeTouchpad();
}

void InterfaceHandler::triggerCurrentHotkey()
{
	if (current_word != "") {
		triggerHotkey(current_word);
		current_word = "";
	}

}

void InterfaceHandler::triggerHotkey(std::string command)
{

	std::string hotkey;
	/*if (command == "stop") {
		//combineToKeyboard("Ctrl+S");
		//Sleep(100);
		pop_window_p->show();
		pop_window_p->showTextRed("TERMINATED");
		Sleep(1000);
		exit(true);
	}
	else */ 
	if (command == "define") {
		pop_window_p->show();
		pop_window_p->showTextRed("Command");
	}
	else {
		if (command != "") {
			hotkey = workingWindow->getHotkeyByCommand(command);
			combineToKeyboard(hotkey);
		}
			
	}
}

/*************************
*   UI Tool Functions
*************************/
void InterfaceHandler::setStrokeColorByName(std::string str) {
	int r, g, b;
	if (str.length() >= 3) {
		r = (int)(((str[0] - 'a') % 26) / 26.0 * 140) + 87;
		g = (int)(((str[1] - 'a') % 26) / 26.0 * 140) + 87;
		b = (int)(((str[2] - 'a') % 26) / 26.0 * 140) + 87;
	}

	penColor.setRed(r);
	penColor.setGreen(g);
	penColor.setBlue(b);

}

std::string InterfaceHandler::getActiveWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
	HMODULE hWndMod = (HMODULE)GetWindowLongA(hwnd, GWLP_HINSTANCE);
	DWORD dwPID;
	GetWindowThreadProcessId(hwnd, &dwPID);
	HANDLE Handle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		dwPID
	);
	char Buffer[MAX_PATH];
	UINT32 bufferLength = 0;
	BYTE* buffer = (PBYTE)malloc(bufferLength);
	PACKAGE_ID* packageId;

	char name[MAX_PATH];
	if (Handle)
	{

		if (GetModuleFileNameExA(Handle, 0, Buffer, sizeof(Buffer)))
		{
			LONG result = GetPackageId(Handle, &bufferLength, nullptr);
			result = GetPackageId(Handle, &bufferLength, buffer);
			packageId = reinterpret_cast<PACKAGE_ID*>(buffer);
			packageId->name;
			// At this point, buffer contains the full path to the executable
		}
		CloseHandle(Handle);
	}

	string str = Buffer;
	string label = str.substr(str.find_last_of('\\') + 1);
	label = label.substr(0, label.find('.'));
	label.erase(0, label.find_first_not_of(" "));
	label.erase(label.find_last_not_of(" ") + 1);
	std::transform(label.begin(), label.end(), label.begin(), ::tolower);
	return label;
}

void InterfaceHandler::setWorkingWindow() {
	this->windowTitle = getActiveWindowTitle();
	window_hotkey_iter = window_hotkey_map.find(this->windowTitle);
	if (window_hotkey_iter != window_hotkey_map.end()) {
		workingWindow = window_hotkey_iter->second;
	}
	else {
		workingWindow = window_hotkey_map.find("-")->second;
	}

	dict = workingWindow->wdict;
	setStrokeColorByName(this->windowTitle);
}

/*************************
*   Data Tool Functions
*************************/

int InterfaceHandler::createComandHotkey(std::string cmd, std::string hotkey) {
	pop_window_p->close();
	this->windowTitle = getActiveWindowTitle();
	pop_window_p->show();

	window_hotkey_iter = window_hotkey_map.find(this->windowTitle);
	if (window_hotkey_iter != window_hotkey_map.end()) {
		int status = window_hotkey_iter->second->existStatus(cmd, hotkey);
		if (status != 0) {
			return status;
		}
		window_hotkey_iter->second->addCommand(cmd, hotkey);
	}
	else {
		window_hotkey_map.insert(std::pair<std::string, WindowHotkey*>
			(this->windowTitle, new WindowHotkey(this->windowTitle, cmd, hotkey)));
		std::ofstream fout("menu_hotkey_label.txt",std::ios_base::app | std::ios_base::out);
		fout << "\n"+cmd+","+hotkey+","+this->windowTitle;
	}
	return 0;
}
void InterfaceHandler::initDict() {
	std::ifstream fin("menu_hotkey_label.txt");
	std::string s;
	std::string word;
	std::string hotkey;
	std::string label;

	while (getline(fin, s)) {
		word = s.substr(0, s.find(','));
		std::string sub1 = s.substr(s.find(',') + 1);
		hotkey = sub1.substr(0, sub1.find(','));
		label = sub1.substr(sub1.find(',') + 1);
		window_hotkey_iter = window_hotkey_map.find(label);
		if (window_hotkey_iter != window_hotkey_map.end()) {
			window_hotkey_iter->second->addCommand(word, hotkey);
		}
		else {
			window_hotkey_map.insert(std::pair<std::string, WindowHotkey*>
				(label, new WindowHotkey(label, word, hotkey)));
		}
		//short_cut_list.push_back(hotkey);
		//test_window_p->addMenuItem(word, hotkey, label);
	}
	window_hotkey_iter = window_hotkey_map.find("-");
	if (window_hotkey_iter != window_hotkey_map.end()) {
		Dictionary* uni_dict = window_hotkey_iter->second->wdict;
		for (std::map<std::string, WindowHotkey*>::iterator iter = window_hotkey_map.begin();
			iter != window_hotkey_map.end(); iter++) {
			if (iter != window_hotkey_iter) {
				iter->second->wdict->expand(*uni_dict);
				iter->second->addCommandsByMap(window_hotkey_iter->second->menu_hotkey_map);
			}
				
		}
	}
	
}

std::vector<char> InterfaceHandler::splitStringToVector(std::string str) {
	std::istringstream ss(str);
	std::string token;

	std::vector<std::string> strVector;
	std::vector<char> cmdVector;
	while (std::getline(ss, token, '+')) {
		strVector.push_back(token);
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);
		//Convert token to vk_code
		if (token == "ctrl")
			cmdVector.push_back(VK_LCONTROL);
		else if (token == "alt")
			cmdVector.push_back(VK_MENU);
		else if (token == "shift")
			cmdVector.push_back(VK_SHIFT);
		else if (token == "win") {
			cmdVector.push_back(VK_LWIN);
		}
		else if (token.size() == 1) {
			if ((token[0] >= '0') && (token[0] <= '9'))
				cmdVector.push_back(token[0]);
			else if((token[0] >= 'a') && (token[0] <= 'z'))
				cmdVector.push_back(toupper(token[0]));
			else
				cmdVector.push_back(VkKeyScanA(token[0]));
		}
	}
	return cmdVector;
}

void InterfaceHandler::combineToKeyboard(std::string combine) {
	std::vector<char> cmds = splitStringToVector(combine);
	std::vector<char>::iterator it;
	for (it = cmds.begin(); it != cmds.end(); it++) {
		keybd_event(*it, 0, 0, 0);
	}
	Sleep(10);
	for (it = cmds.begin(); it != cmds.end(); it++) {
		keybd_event(*it, 0, KEYEVENTF_KEYUP, 0);
	}
}

int InterfaceHandler::getSysKeyStatus() {
	int comb_key = 0;
	if ((GetKeyState(VK_LBUTTON) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
		comb_key += P_LBUTTON;
	
	if ((GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
		comb_key += P_CTRL;
	if ((GetAsyncKeyState(VK_MENU) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
		comb_key += P_ALT;
	if ((GetAsyncKeyState(VK_SHIFT) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
		comb_key += P_SHIFT;
	
	return comb_key;
}

/*************************
*      QT UI Functions
*************************/
void InterfaceHandler::windowToCursor() {
	test_window_p->setWindowToCursor();
}

void InterfaceHandler::draw_point(Point<long>& p, bool isTouching)
{
	test_window_p->clearFocus();
	test_window_p->draw_point(penColor,p, isTouching);
}

void InterfaceHandler::clear_canvas()
{
	test_window_p->clear_canvas();
}

void InterfaceHandler::showCanvas()
{
	if (test_window_p == NULL) {
		test_window_p = new SettingWindow();
	}
	test_window_p->setWindowFlags(Qt::FramelessWindowHint);
	test_window_p->setAttribute(Qt::WA_TranslucentBackground, true);
	test_window_p->setWindowOpacity(TRANSPARENCY);
	
	test_window_p->show();
	test_window_p->raise();
	test_window_p->activateWindow();
}

void InterfaceHandler::hideCanvas()
{
	test_window_p->hide();
}

void InterfaceHandler::showText(std::string str,std::string hk)
{
	test_window_p->showText(str, hk);
	//test_window_p->show();
}

