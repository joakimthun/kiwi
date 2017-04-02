#include "util.h"

#include <cstdlib>

namespace kiwi {

	float f_rand()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

}