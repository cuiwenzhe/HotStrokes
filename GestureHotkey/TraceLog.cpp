#include "TraceLog.h"
#include <direct.h>      
#include <io.h>  
#include <iostream>  
#include <fstream>
#include <string>
#include <ctime>
void WordLog::gesture_to_wordlog(GestureKey &trace)
{
	TraceItem t_point;
	t_point.user_id = id;
	strock_index = 0;
	std::string s="<";
	s.append(word);
	s.append(">");
	t_point.current_target = s;

	trace.iter = trace.raw_points.begin();
	for (trace.iter; 
		trace.iter != trace.raw_points.end(); trace.iter++) {
		t_point.x_keyboard = trace.iter->x;
		t_point.y_keyboard = trace.iter->y;
		t_point.screen_x = trace.iter->x;
		t_point.screen_y = trace.iter->y;
		t_point.index_on_stroke = strock_index++;
		word_point.push_back(t_point);
	}
}
void TraceLog::createFile() {
	path = ".\\collection";
	filename = path + "\\"+user_name+"_";
	filename.append(user_id);
	if (_access(path.c_str(), 0) == -1)
	{
		int i = _mkdir(path.c_str());
	}

	if (_access(filename.c_str(), 0) != -1)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%d%m%Y_%I%M%S", timeinfo);
		std::string str(buffer);
		filename.append(str);
	}
	filename.append("_TouchpadGesture_GesturePoints");
}
void TraceLog::printlog()
{	
	std::vector<WordLog>::const_iterator w_iter;
	std::vector<TraceItem>::const_iterator p_iter;

	std::ofstream of(filename);
	std::ifstream inf ("logheader.txt");
	of << inf.rdbuf();
	for (w_iter = log.begin(); w_iter != log.end(); ++w_iter) {
		for (p_iter = w_iter->word_point.begin();
			p_iter != w_iter->word_point.end(); ++p_iter) {
			std::string str;
			str.push_back(p_iter->input_finger);
			str.append(",");
			str.append(p_iter->user_id);
			str.append(",");
			str.append(p_iter->keyboard_type);
			str.append(",");
			str.append(std::to_string(p_iter->task_type));
			str.append(",");
			str.append(std::to_string(p_iter->block_num));
			str.append(",");
			str.append(std::to_string(p_iter->trial_num));
			str.append(",");
			str.append(p_iter->phrase);
			str.append(",");
			str.append(std::to_string(p_iter->posOnPhrase));
			str.append(",");
			str.append(p_iter->current_target);
			str.append(",");
			str.append(std::to_string(p_iter->index_on_stroke));
			str.append(",");
			str.append(std::to_string(p_iter->pointer_id));
			str.append(",");
			str.append(std::to_string(p_iter->x_keyboard));
			str.append(",");
			str.append(std::to_string(p_iter->y_keyboard));
			str.append(",");
			str.append(std::to_string(p_iter->screen_x));
			str.append(",");
			str.append(std::to_string(p_iter->screen_y));
			str.append(",");
			str.append(std::to_string(p_iter->event_time));
			str.append(",");
			str.append(std::to_string(p_iter->system_time));
			str.append(",");
			str.append(std::to_string(p_iter->time_up_now));
			str.append(",");
			str.append(p_iter->action_type);
			str.append(",");
			str.append(std::to_string(p_iter->is_gesture_expert));
			str.append(",");
			str.append(std::to_string(p_iter->user_index));
			str.append(",");
			str.append(p_iter->device);
			str.append(",");
			str.append(std::to_string(p_iter->input_mode));
			str.append(",");
			str.append(std::to_string(p_iter->pressure));
			str.append(",");
			str.append(std::to_string(p_iter->size));
			str.append(",");
			str.append(std::to_string(p_iter->touch_major));
			str.append(",");
			str.append(std::to_string(p_iter->touch_minor));
			str.append(",");
			str.append(std::to_string(p_iter->tool_major));
			str.append(",");
			str.append(std::to_string(p_iter->tool_minor));
			str.append(",");
			str.append(std::to_string(p_iter->x_precision));
			str.append(",");
			str.append(std::to_string(p_iter->y_precision));
			str.append(",");
			str.append(std::to_string(p_iter->historical_pos));
			str.append(",");
			str.append(std::to_string(p_iter->is_cancelled));

			of << str << std::endl;
		}
	}
}
