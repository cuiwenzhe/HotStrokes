#include "Dictionary.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::ifstream;
using std::list;

Dictionary::Dictionary(const char* f)
{
	string s;
	ifstream fin(f);
	while (getline(fin, s)) {
		WordTrace wt(s);
		gest_dict.push_back(wt);
	}
}

void Dictionary::addWord(std::string word) {
	WordTrace wt(word);
	gest_dict.push_back(wt);
}

void Dictionary::expand(Dictionary & dict)
{
	gest_dict.insert(gest_dict.begin(), dict.gest_dict.begin(), dict.gest_dict.end());
}

void Dictionary::calculate_words_score(GestureKey g)
{
	for (list<WordTrace>::iterator it = gest_dict.begin();
		it != gest_dict.end(); ++it) {
		double pos_error = GestureKey::get_position_error(g, it->get_g_word());
		double shape_error = GestureKey::get_shape_error(g, it->get_g_word());
		double shark2_error = 0.76*shape_error + 0.24*pos_error;
		it->set_score(shark2_error);
	}
	gest_dict.sort(WordTrace::compare);
}
