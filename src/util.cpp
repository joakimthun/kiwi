#include "util.h"

#include <cstdlib>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "win32/win32_window.h"
#include "sdl_window.h"

namespace kiwi {

	float f_rand()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	float clamp(float value, float min, float max)
	{
		if (value > max)
			return max;

		if (value < min)
			return min;

		return value;
	}

	TriangleAreaSign triangle_area_sign(const Vertex &min_y, const Vertex &max_y, const Vertex &mid_y)
	{
		// Vector from min to max
		float x1 = max_y.x() - min_y.x();
		float y1 = max_y.y() - min_y.y();

		// Vector from min to mid
		float x2 = mid_y.x() - min_y.x();
		float y2 = mid_y.y() - min_y.y();

		// Positive cross product?
		return (x1 * y2 - x2 * y1) >= 0 ? TriangleAreaSign::Positive : TriangleAreaSign::Negative;
	}
	
	// http://stackoverflow.com/questions/236129/split-a-string-in-c++
	template<typename Out>
	void str_split(const std::string &s, char delim, Out result) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}

	std::vector<std::string> remove_empty_str_entries(const std::vector<std::string> src)
	{
		std::vector<std::string> result;
		std::back_insert_iterator<std::vector<std::string>> back_it(result);

		std::copy_if(src.begin(), src.end(), back_it, [](const std::string &value)
		{ 
			return value != "" && value != " ";
		});

		return result;
	}

	std::vector<std::string> str_split(const std::string &s, char delim, RemoveEmptyEntries remove_empty_entries) {
		std::vector<std::string> elems;
		str_split(s, delim, std::back_inserter(elems));

		if (remove_empty_entries == RemoveEmptyEntries::Yes)
			return remove_empty_str_entries(elems);

		return elems;
	}

	std::unique_ptr<Window> create_window(int32_t width, int32_t height)
	{
#if 0
		return std::make_unique<Win32Window>(width, height);
#endif
		return std::make_unique<SDLWindow>(width, height);
		
	}
}