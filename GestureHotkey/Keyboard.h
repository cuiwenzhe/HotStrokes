#ifndef KEYBOARD
#define KEYBOARD

#include "Containers.h"
#include <vector>
#include <string>
#include <math.h>

#define KEY_WIDTH_NEXUS_5X 500.0
#define KEY_HEIGHT_NEXUS_5X 1333.3

extern const double keyXArr_NEXUS_5X[26];
extern const double keyYArr_NEXUS_5X[26];

class GestureKey {
public:
	friend class WordLog;

	GestureKey() :maxlen(0.0), normalized(false) {}
	GestureKey(std::string& s) :maxlen(0.0), normalized(false) { set_word_points(s); }

	void push_back(Point<double> point) {
		raw_points.push_back(point);
	}
	void push_back(Point<long> point) {
		Point<double> p((double)point.x, (double)point.y);
		raw_points.push_back(p);
	}
	void clear() {
		raw_points.clear();
		sampled_points.clear();
		resampled_points.clear();
		unnormal_resampled_points.clear();

		distances.clear();
		maxlen = 0;
		normalized = false;
	}
	bool is_normalized() const { return normalized; }
	void set_word_points(std::string& s, int N = 100) {
		if (!normalized) clear();
		set_phrase_coordinate(s);
		normalize_resample_points(N);
	}
	void set_phrase_coordinate(std::string&);
	bool isEmpty();
	void normalize_resample_points(int N);
	double get_maxlen() { return maxlen; }
	static double get_distance(const Point<double>&, const Point<double>&);
	static double get_position_error(GestureKey & k1, GestureKey & k2);
	static double get_shape_error(GestureKey&, GestureKey&);
private:
	std::vector<Point<double> > raw_points;
	std::vector<Point<double> > sampled_points;
	std::vector<Point<double> > resampled_points;
	std::vector<Point<double> > unnormal_resampled_points;
	std::vector<double> distances;
	Point<double> center;
	double maxlen;
	bool normalized;
	std::vector<Point<double> >::const_iterator iter;
	void set_resample_point(int N);
	void set_scale_centroid();
};

#endif
