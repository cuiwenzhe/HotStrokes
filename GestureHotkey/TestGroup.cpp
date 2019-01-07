#include "TestGroup.h"
#include <fstream>
using std::string;
using std::vector;
using std::ifstream;

WordSection::WordSection(std::istream & is, section_size size):pos(0)
{
	string word;
	section_size count = 0;
	
	//the order of Determine statements cannot be changed
	while (count++ != size && getline(is, word)) {
		section.push_back(word);
	}
	iter = section.begin();
}

bool WordSection::getNext(std::string & str)
{
	if (iter != section.end()) {
		str = *iter++;
		pos = iter-section.begin();
		return true;
	}
	pos = 0;
	iter = section.begin();
	return false;
}

WordSection::section_size WordSection::getPos()
{
	return pos;
}

TestGroup::TestGroup(std::istream &is, test_size t_size, section_size s_size)
	:sections_num(s_size)
{
	getGroupByFile(is, t_size, s_size);
}

TestGroup::TestGroup(const char * s, test_size t_size, section_size s_size)
{
	std::ifstream is(s);
	getGroupByFile(is, t_size, s_size);
}

// -1: group end, 0: section end, 1: get a word
int TestGroup::getNext(std::string &str)
{
	if (group_iter != group.end()) {
		if (!group_iter->getNext(str)) {
			++group_iter;
			if (group_iter == group.end()) {
				group_iter = group.begin();
				return -1;
			}		
			group_iter->getNext(str);
			return 0;
		}
		return 1;
	}
	group_iter = group.begin();
	return -1;
}

int TestGroup::getGroup()
{
	return group_iter - group.begin() + 1;
}

int TestGroup::getPosInGroup()
{
	
	return group_iter->getPos();
}

bool TestGroup::isRepeat()
{
	if (++counter == word_repeat_times) {
		counter = 0;
		return false;
	}
	return true;
}

void TestGroup::getGroupByFile(std::istream &is, test_size t_size, section_size s_size) {
	while (is) {
		WordSection WS = WordSection(is, s_size);
		if (WS.size() != 0) 
			group.push_back(WS);

	}
	group_iter = group.begin();
}


