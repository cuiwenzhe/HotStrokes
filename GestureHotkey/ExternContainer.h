#ifndef EXTERNCONTAINER_H
#define EXTERNCONTAINER_H

#define P_CTRL 1
#define P_ALT 10
#define P_SHIFT 20
#define P_CTRL_ALT 11
#define P_CTRL_SHIFT 21
#define P_ALT_SHIFT 30
#define P_CTRL_ALT_SHIFT 31
#define P_RELEASE_KEY 0
#define P_LBUTTON 4
#define TRANSPARENCY 0.9

#define CMD_OCCUPIED -1
#define HOTKEY_OCCUPIED -2

#include "TestGroup.h"
#include "Dictionary.h"
#include "TraceLog.h"
#include "GestureHotkey.h"
#include "WindowHotkey.h"
#include <QColor>

extern TraceLog tracelog;
extern GestureKey touch_trace;
extern Dictionary* dict;
extern bool gesture_test_flag;

class InterfaceHandler {
public:
	InterfaceHandler():test_window_p(NULL), word_window_p(NULL), pop_window_p(NULL){}
	InterfaceHandler(GestureHotkey* tw)
		:test_window_p(tw){
	}
	void setTestWindow(GestureHotkey* tw) { test_window_p = tw; }
	void setWordWindow(WordWindow* ww) { word_window_p = ww; }
	void setPopWindow(WordWindow* pw) { pop_window_p = pw; }
	
	void triggerCurrentHotkey();
	void triggerHotkey(std::string word);
	void combineToKeyboard(std::string combine);
	std::vector<char> splitStringToVector(std::string);
	void showText(std::string str, std::string hk);
	void windowToCursor();
	int createComandHotkey(std::string cmd, std::string hotkey);
	void initDict();
	std::string getActiveWindowTitle();
	void setWorkingWindow();
	void setStrokeColorByName(std::string str);
	void handleTrace(GestureKey & trace);
	void draw_point(Point<long>& p, bool isTouching);
	int getSysKeyStatus();
	void clear_canvas();
	void showCanvas();
	void hideCanvas();
	void checkShortcut(std::string);
	//void draw_point(Point<long>&);
public:
	std::map<std::string, WindowHotkey*> window_hotkey_map;
private:
	std::map<std::string, WindowHotkey*>::iterator window_hotkey_iter;
	GestureHotkey * test_window_p;
	WordWindow *word_window_p;
	WordWindow *pop_window_p;
	std::string wordstr;
	std::string current_word="";
	std::string windowTitle="";
	WindowHotkey* workingWindow;
	QColor penColor = QColor(0,0,0);
	
};

extern InterfaceHandler interface_handler;

#endif