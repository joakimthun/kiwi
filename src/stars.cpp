#include "stars.h"

#include "util.h"
#include "renderer.h"

namespace kiwi {

	Stars::Stars(std::size_t num_stars, float spread, float speed)
		:
		num_stars_(num_stars),
		spread_(spread),
		speed_(speed)
	{
		stars_x_.resize(num_stars);
		stars_y_.resize(num_stars);
		stars_z_.resize(num_stars);

		for (auto i = 0; i < num_stars; i++)
		{
			init_star(i);
		}
	}

	void Stars::frame(Renderer *renderer, float delta)
	{
		renderer->clear(0, 0, 0);

		auto width = renderer->width();
		auto height = renderer->height();
		auto half_width = width / 2.0f;
		auto half_height = height / 2.0f;

		for (auto i = 0; i < num_stars_; i++)
		{
			// Move it towards the camera, at z 0
			stars_z_[i] -= delta * speed_;

			// If a star is behind the camera, reset it's position
			if (stars_z_[i] <= 0)
			{
				init_star(i);
			}

			// Map from -1, 1 to 0 width/heigth
			int x = (int)((stars_x_[i] / stars_z_[i]) * half_width + half_width);
			int y = (int)((stars_y_[i] / stars_z_[i]) * half_height + half_height);

			// If a star is out of bounds, reset it's position
			if (x < 0 || x >= width || (y < 0 || y >= height))
			{
				init_star(i);
			}
			else
			{
				renderer->put_pixel(x, y, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	void Stars::init_star(std::size_t i)
	{
		// Put star at a -1 to 1
		stars_x_[i] = 2 * (f_rand() - 0.5f) * spread_;
		stars_y_[i] = 2 * (f_rand() - 0.5f) * spread_;
		
		stars_z_[i] = (f_rand() + 0.00001f) * spread_;
	}

}
