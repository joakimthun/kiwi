#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "glm/vec4.hpp"

namespace kiwi {
	namespace models {

		struct OBJIndex
		{
			int32_t vertex;
			int32_t text_coord;
			int32_t normal;
		};

		class Obj
		{
		public:
			Obj(const std::string &filename);

		private: 
			void load(const std::string &filename);
			OBJIndex parse_obj_index(const std::string &token);

			std::vector<glm::vec4> positions_;
			std::vector<glm::vec4> tex_coords_;
			std::vector<glm::vec4> normals_;
			std::vector<OBJIndex> indices_;
			bool has_tex_coords_;
			bool has_normals_;
		};
	}
}