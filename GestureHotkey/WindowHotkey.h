#pragma once
#include "Dictionary.h"
#include <String>
#include <map>

using namespace std;

class WindowHotkey {
public:
	WindowHotkey(string& label) :title(label) {
		wdict = new Dictionary();
	};
	WindowHotkey(string& label, string& word, string& hotkey) :title(label) {
		wdict = new Dictionary();
		addCommand(word, hotkey);
	};
	bool isTitleMatch(string& label) {
		if (label == "-")
			return true;
		return label == this->title;
	}
	void addCommand(string word, string hotKey) {
		wdict->addWord(word);
		menu_hotkey_map.insert(pair<string, string>(word, hotKey));
	}
	int existStatus(string word, string hotkey) {
		for (pair<string, string> whPair : menu_hotkey_map) {
			if (whPair.first == word) {
				return CMD_OCCUPIED;
			}
			else if (whPair.second == hotkey) {
				return HOTKEY_OCCUPIED;
			}
		}
		return 0;
	}
	void addCommandsByMap(map<string, string> new_map) {
		menu_hotkey_map.insert(new_map.begin(), new_map.end());
	}
	string getHotkeyByCommand(string command) {
		return menu_hotkey_map.find(command)->second;
	}
public:
	Dictionary * wdict;
	map<string, string> menu_hotkey_map;
private:
	string title;
	

};
