#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

#include "indexed_model.h"
#include "../math/vec4.h"

namespace kiwi {

	struct OBJIndex
	{
		std::size_t vertex;
		std::size_t text_coord;
		std::size_t normal;

		bool operator==(const OBJIndex &other) const
		{
			return vertex == other.vertex
				&& text_coord == other.text_coord
				&& normal == other.normal;
		}
	};

	class ObjModel
	{
	public:
		static std::unique_ptr<IndexedModel> from_file(const std::string &filename);

	private:
		ObjModel(const std::string &filename);
		std::unique_ptr<IndexedModel> to_indexed_model();
		void load(const std::string &filename);
		OBJIndex parse_obj_index(const std::string &token);

		std::vector<Vec4> positions_;
		std::vector<Vec4> tex_coords_;
		std::vector<Vec4> normals_;
		std::vector<OBJIndex> indices_;
		bool has_tex_coords_;
		bool has_normals_;
	};
}