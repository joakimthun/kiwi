#pragma once

#include <stdint.h>
#include <vector>

namespace kiwi {

	class Renderer;

	class Stars
	{
	public:
		Stars(std::size_t num_stars, float spread, float speed);

		void frame(Renderer *renderer, float delta);
	private:
		void init_star(std::size_t i);

		const std::size_t num_stars_;
		const float spread_;
		const float speed_;
		std::vector<float> stars_x_;
		std::vector<float> stars_y_;
		std::vector<float> stars_z_;
	};

}