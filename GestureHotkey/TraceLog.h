#ifndef TRACE_LOG_H
#define TRACE_LOG_H

#include "Keyboard.h"
#include "TestGroup.h"
#include <string>
#include <istream>
#include <vector>

#define SECTION_SIZE 5;

struct TraceItem {
	char input_finger = 'i';
	std::string user_id = "9527";
	std::string keyboard_type = "touchpad";
	int task_type = -1;
	int block_num = -1;
	int trial_num = -1;
	std::string phrase = "";
	int posOnPhrase = -1;
	std::string current_target = "";
	int index_on_stroke = -1;
	int pointer_id = -1;
	double x_keyboard = -1.0;
	double y_keyboard = -1.0;
	double screen_x = -1.0;
	double screen_y = -1.0;
	long event_time = -1;
	long system_time = -1;
	long time_up_now = -1;
	std::string action_type = "";
	bool is_gesture_expert = false;
	int user_index = -1;
	std::string device = "Thinkpad X1 Carbon 2017";
	int input_mode = -1;
	double pressure = -1.0;
	double size = -1.0;
	double touch_major = -1.0;
	double touch_minor = -1.0;
	double tool_minor = -1.0;
	double tool_major = -1.0;
	int x_precision = -1;
	int y_precision = -1;
	int historical_pos = -1;
	int is_cancelled = -1;
	
};

class TraceLog {
public:
	friend class WordLog;
	TraceLog():log(),index(0) {}
	void createFile();
	//TraceLog(std::string name, std::string id, char finger,std::istream is) :user_id(id), input_finger(finger), t_group(is, SECTION_SIZE, SECTION_SIZE) {}
	void printlog();
	void setUserId(std::string& id) { user_id = id; }
	void setUserName(std::string& name) { user_name = name; }
	void setUserFinger(char finger) { input_finger = finger; }
	void push_back(WordLog& w_log) {
		log.push_back(w_log);
		++index;
	}
private:
	std::string path = ".\\collection";
	std::string filename = ".\\collection\\user_";
	std::string user_id = "";
	std::string user_name = "";
	char input_finger = 'i';
	std::vector<WordLog> log;
	int index;
	TestGroup t_group;
};
class WordGroup {

};


class WordLog {
	typedef std::vector<TraceItem>::size_type size_t;
public:
	friend class TraceLog;
	WordLog() :word(""), strock_index(-1) {}
	WordLog(TraceLog& tl, std::string& wordstr) :
		id(tl.user_id), word(wordstr), strock_index(0) {
	}
	WordLog(std::string uid, std::string str, int index)
		:id(uid), word(str), strock_index(index) {
	}
	void gesture_to_wordlog(GestureKey&);
private:
	std::string id;
	std::vector<TraceItem> word_point;
	std::string word;
	int strock_index;
};

#endif