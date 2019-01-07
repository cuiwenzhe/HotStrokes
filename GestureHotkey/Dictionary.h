#ifndef DICTIONARY
#define DICTIONARY
#include "Keyboard.h"
#include <vector>
#include <list>

class WordTrace {
public:
	WordTrace(std::string s) :score(0), word("") {
		word = s;
		g_word.set_word_points(s);
	}
	GestureKey& get_g_word() { return g_word; }
	void set_score(double sc) { score = sc; }
	std::string get_word() const { return word; }
	double get_score() const { return score;  }
	static bool compare(const WordTrace& w1, const WordTrace& w2) {
		return w1.score < w2.score;
	}
private:
	double score;
	std::string word;
	GestureKey g_word;
};

class Dictionary {
public:
	Dictionary(const char*);
	Dictionary() {};
	std::string get_first_word() {
		return gest_dict.begin()->get_word();
	}
	double get_first_word_error(
	) {
		return gest_dict.begin()->get_score();
	}
	std::string get_word_by_index(std::list<WordTrace>::size_type r) const {
		if (r >= gest_dict.size()) return "";
		std::list<WordTrace>::const_iterator iter = gest_dict.begin();
		while (r--) ++iter;
		return iter->get_word();
	}
	void addWord(std::string);
	void expand(Dictionary& dict);
	void calculate_words_score(GestureKey g);
private:
	std::list<WordTrace> gest_dict;
};


#endif