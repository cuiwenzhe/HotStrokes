#ifndef TEST_GROUP
#define TEST_GROUP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class WordSection {
	typedef std::vector<std::string>::size_type section_size;
public:
	WordSection() :section(), iter(section.begin()), pos(0){};
	WordSection(std::istream&, section_size);
	WordSection(const WordSection& ws):pos(0) {
		section = ws.section;
		iter = section.begin();
	}
	WordSection operator=(const WordSection& ws) {
		if (&ws != this) {
			section = ws.section;
			iter = section.begin();
		}
		return *this;
	}
	~WordSection() {};
	bool getNext(std::string&);
	section_size getPos();
	section_size size() { return section.size(); };
private:
	std::vector<std::string>::iterator iter;
	std::vector<std::string> section;
	section_size pos;
};

class  TestGroup {
	typedef std::vector<WordSection>::size_type test_size;
	typedef std::vector<std::string>::size_type section_size;
	typedef std::vector<WordSection>::iterator c_iter;
public:
	TestGroup() :group(), sections_num(0), group_iter(group.begin()) {}
	TestGroup(std::istream&, test_size, section_size);
	TestGroup(const char*, test_size t_size, section_size s_size);
	test_size size() { return group.size(); }
	section_size sections_size() { return sections_num; }
	int getNext(std::string&);//get next word in wordsection
	int getGroup();
	int getPosInGroup();
	bool isRepeat();
	int get_repeat_times() { return counter; }
private:
	int counter = 0;
	int word_repeat_times = 3;
	c_iter group_iter;
	test_size sections_num;
	std::vector<WordSection> group;
	void TestGroup::getGroupByFile(std::istream&, test_size, section_size);
};
#endif