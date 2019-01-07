#include "keyboard.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>

using std::string;
using std::vector;

const double keyXArr_NEXUS_5X[26] = {
	0.5 * KEY_WIDTH_NEXUS_5X, 5.5 * KEY_WIDTH_NEXUS_5X, 3.5 * KEY_WIDTH_NEXUS_5X, 2.5 * KEY_WIDTH_NEXUS_5X, 2 * KEY_WIDTH_NEXUS_5X, // a~e
	3.5 * KEY_WIDTH_NEXUS_5X, 4.5 * KEY_WIDTH_NEXUS_5X, 5.5 * KEY_WIDTH_NEXUS_5X, 7 * KEY_WIDTH_NEXUS_5X, 6.5 * KEY_WIDTH_NEXUS_5X, // f-j
	7.5 * KEY_WIDTH_NEXUS_5X, 8.5 * KEY_WIDTH_NEXUS_5X, 7.5 * KEY_WIDTH_NEXUS_5X, 6.5 * KEY_WIDTH_NEXUS_5X, 8 * KEY_WIDTH_NEXUS_5X, // k-o
	9 * KEY_WIDTH_NEXUS_5X, 0, 3 * KEY_WIDTH_NEXUS_5X, 1.5 * KEY_WIDTH_NEXUS_5X, 4 * KEY_WIDTH_NEXUS_5X, // p - t
	6 * KEY_WIDTH_NEXUS_5X, 4.5 * KEY_WIDTH_NEXUS_5X, KEY_WIDTH_NEXUS_5X, 2.5 * KEY_WIDTH_NEXUS_5X, 5 * KEY_WIDTH_NEXUS_5X, 1.5 * KEY_WIDTH_NEXUS_5X  // u - z
};
const double keyYArr_NEXUS_5X[26] = {
	1.5 * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, // a~e
	1.5 * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, // f-j
	1.5 * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, // k -o
	0.5 * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, 1.5 * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, // p - t
	0.5 * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, 2.5  * KEY_HEIGHT_NEXUS_5X, 0.5 * KEY_HEIGHT_NEXUS_5X, 2.5 * KEY_HEIGHT_NEXUS_5X // u - z
};
/*
const double keyXArr_NEXUS_5X[26] = {
997.14, 2636.41, 1833.02, 1585.01, 1620.06, // a~e
1852.99, 2312.79, 2697.37, 3188.52, 2794.89, // f-j
3460.16, 3761.24, 3229.76, 2834.74, 3399.90, // k-o
4065.76, 627.71, 2139.04, 1307.93, 2134.53, // p - t
2907.69, 2256.75, 1218.92, 1440.33, 2864.31, 853.07  // u - z
};
const double keyYArr_NEXUS_5X[26] = {
796.99, 1864.44, 1759.68, 931.33, 207.83, // a~e
1156.13, 899.74, 959.16, 161.38, 960.88, // f-j
567.09, 876.48, 1568.91, 1814.08, 185.25, // k -o
250.88, 793.70, 162.96, 1004.12, 217.92, // p - t
126.94, 1709.99, 298.15, 1878.70, 274.79, 1634.07, // u - z
};*/

void GestureKey::set_phrase_coordinate(std::string &s)
{
	for (string::const_iterator i = s.begin();
		i != s.end(); ++i) {
		Point<double> p(keyXArr_NEXUS_5X[*i - 'a'], keyYArr_NEXUS_5X[*i - 'a']);
		raw_points.push_back(p);
	}
}

bool GestureKey::isEmpty()
{
	return raw_points.empty();
}

//resample raw points to N points with average step
void GestureKey::set_resample_point(int N)
{
	typedef vector<Point<double> >::const_iterator vp_const_iterator;
	typedef vector<Point<double> >::size_type size_type;
	if (!raw_points.empty()) {
		Point<double> p(raw_points[0].x, raw_points[0].y);
		sampled_points.push_back(p);
		//incase a single word making no distance
		if (raw_points.size() == 1)
			sampled_points.push_back(p);
		for (vp_const_iterator it_raw = raw_points.begin();
			it_raw != raw_points.end(); ++it_raw) {
			if (get_distance(*it_raw, *(sampled_points.end() - 1)) >= 2.0) {
				sampled_points.push_back(*it_raw);
			}
		}

		for (vp_const_iterator it_sp = sampled_points.begin();
			it_sp != sampled_points.end() - 1; ++it_sp) {
			distances.push_back(get_distance(*it_sp, *(it_sp + 1)));
		}
		double step = std::accumulate(distances.begin(), distances.end(), 0.0) / (double)N;

		for (size_type i = 0; i != N; ++i) {
			double d = i * step; //resample distance
			double searched_dist = 0;
			size_type segment_index = 0;
			bool flag = false;

			for (vector<double>::size_type j = 0;
				j != distances.size(); j++) {
				searched_dist += distances[j];
				if (searched_dist > d) {
					segment_index = j;
					flag = true;
					break;
				}
			}

			if (flag = false) break;

			//distance of last 2 points when reaching searched_dist
			double dx = sampled_points[segment_index + 1].x - sampled_points[segment_index].x;
			double dy = sampled_points[segment_index + 1].y - sampled_points[segment_index].y;

			double dd = d - searched_dist + distances[segment_index];

			double xx = sampled_points[segment_index].x + dd * dx / distances[segment_index];
			double yy = sampled_points[segment_index].y + dd * dy / distances[segment_index];

			Point<double> resp(xx, yy);
			resampled_points.push_back(resp);
		}
		while (resampled_points.size() < N)
			resampled_points.push_back(*(sampled_points.end() - 1));
	}

}

void GestureKey::set_scale_centroid()
{
	double max_x = resampled_points[0].x;
	double max_y = resampled_points[0].y;
	double min_x = resampled_points[0].x;
	double min_y = resampled_points[0].y;
	if (resampled_points.size() != 0) {
		for (vector<Point<double> >::const_iterator it = resampled_points.begin();
			it != resampled_points.end(); ++it) {
			max_x = it->x > max_x ? it->x : max_x;
			min_x = it->x < min_x ? it->x : min_x;
			max_y = it->y > max_y ? it->y : max_y;
			min_y = it->y < min_y ? it->y : min_y;
		}
		center.x = std::abs(max_x - min_x) / 2.0 + min_x;
		center.y = std::abs(max_y - min_y) / 2.0 + min_y;
		maxlen = std::max(std::abs(max_x - min_x), std::abs(max_y - min_y));
	}
}

void GestureKey::normalize_resample_points(int N)
{
	set_resample_point(N);
	set_scale_centroid();
	unnormal_resampled_points = resampled_points;

	double scale = maxlen;

	if (scale != 0.0) { scale = 1.0 / scale; }

	for (vector<Point<double> >::iterator it = resampled_points.begin();
		it != resampled_points.end(); ++it) {
		it->x = (it->x - center.x)*scale;
		it->y = (it->y - center.y)*scale;
	}
	normalized = true;
	//normalization
}

double GestureKey::get_distance(const Point<double>& p1, const Point<double>& p2)
{
	return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

double  GestureKey::get_position_error(GestureKey& k1, GestureKey& k2) {
	typedef vector<Point<double> >::size_type size_type;
	double error = -1.0;
	vector<double> err_distances;
	if (k1.normalized == true && k2.normalized == true)
	{
		size_type N = k1.unnormal_resampled_points.size();
		size_type N2 = k1.unnormal_resampled_points.size();

		if (N != N2) { throw std::domain_error("gestures has different numbers of sampled points"); }

		for (vector<Point<double> >::size_type i = 0;
			i != N; ++i) {
			err_distances.push_back(
				GestureKey::get_distance(k1.unnormal_resampled_points[i], k2.unnormal_resampled_points[i]) / 500.0);
		}
		error = std::accumulate(err_distances.begin(), err_distances.end(), 0.0) / 7.81025 / N;
	}
	return error;
}
double  GestureKey::get_shape_error(GestureKey& k1, GestureKey& k2) {
	typedef vector<Point<double> >::size_type size_type;
	double error = -1.0;
	vector<double> err_distances;
	if (k1.normalized == true && k2.normalized == true)
	{
		size_type N = k1.resampled_points.size();
		size_type N2 = k1.resampled_points.size();

		if (N != N2) { throw std::domain_error("gestures has different numbers of sampled points"); }

		for (vector<Point<double> >::size_type i = 0;
			i != N; ++i) {
			err_distances.push_back(
				GestureKey::get_distance(k1.resampled_points[i], k2.resampled_points[i]));
		}

		error = std::accumulate(err_distances.begin(), err_distances.end(), 0.0) / N;
	}
	return error;
}
