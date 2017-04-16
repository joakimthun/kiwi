#pragma once

#include <stdint.h>
#include <vector>

#include "../math/vec4.h"

namespace kiwi {

	class IndexedModel
	{
	public:
		std::vector<Vec4> &positions();
		std::vector<Vec4> &tex_coords();
		std::vector<Vec4> &normals();
		std::vector<std::size_t> &indices();
		std::vector<Vec4> &tangents();

		void calc_normals();
		void calc_tangents();

	private:
		std::vector<Vec4> positions_;
		std::vector<Vec4> tex_coords_;
		std::vector<Vec4> normals_;
		std::vector<std::size_t> indices_;
		std::vector<Vec4> tangents_;
	};

}
