#pragma once

#include <stdint.h>
#include <vector>
#include "glm/vec4.hpp"

namespace kiwi {

	class IndexedModel
	{
	public:
		std::vector<glm::vec4> &positions();
		std::vector<glm::vec4> &tex_coords();
		std::vector<glm::vec4> &normals();
		std::vector<std::size_t> &indices();
		std::vector<glm::vec4> &tangents();

		void calc_normals();
		void calc_tangents();

	private:
		std::vector<glm::vec4> positions_;
		std::vector<glm::vec4> tex_coords_;
		std::vector<glm::vec4> normals_;
		std::vector<std::size_t> indices_;
		std::vector<glm::vec4> tangents_;
	};

}
