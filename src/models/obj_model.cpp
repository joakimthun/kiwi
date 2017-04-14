#include "obj_model.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "../util.h"

namespace kiwi {

	struct OBJIndexHasher
	{
		std::size_t operator()(const OBJIndex& key) const
		{
			return (key.vertex << 10 ^ key.text_coord << 5 ^ key.normal);
		}
	};

	std::unique_ptr<IndexedModel> ObjModel::from_file(const std::string &filename)
	{
		auto obj = ObjModel(filename);
		return obj.to_indexed_model();
	}

	ObjModel::ObjModel(const std::string &filename)
		:
		has_tex_coords_(false),
		has_normals_(false)
	{
		load(filename);
	}

	std::unique_ptr<IndexedModel> ObjModel::to_indexed_model()
	{
		auto result = std::make_unique<IndexedModel>();
		auto normal_model = IndexedModel();

		std::unordered_map<OBJIndex, int32_t, OBJIndexHasher> result_index_map;
		std::unordered_map<std::size_t, int32_t> normal_index_map;
		std::unordered_map<std::size_t, int32_t> index_map;

		const auto get_map_entry = [](const auto &map, const auto &key)
		{
			auto it = map.find(key);
			if (it != map.end())
			{
				return it->second;
			}

			return -1;
		};

		for (auto i = 0; i < indices_.size(); i++)
		{
			const auto& current_index = indices_[i];

			auto current_position = positions_[current_index.vertex];
			glm::vec4 current_tex_coord(0, 0, 0, 0);
			glm::vec4 current_normal(0, 0, 0, 0);

			if (has_tex_coords_)
				current_tex_coord = tex_coords_[current_index.text_coord];

			if (has_normals_)
				current_normal = normals_[current_index.normal];

			auto model_vertex_index = get_map_entry(result_index_map, current_index);

			if (model_vertex_index == -1)
			{
				model_vertex_index = result->positions().size();
				result_index_map.insert(std::pair<OBJIndex, int32_t>(current_index, model_vertex_index));

				result->positions().push_back(current_position);
				result->tex_coords().push_back(current_tex_coord);
				if (has_normals_)
					result->normals().push_back(current_normal);
			}

			auto normal_model_index = get_map_entry(normal_index_map, current_index.vertex);

			if (normal_model_index == -1)
			{
				normal_model_index = normal_model.positions().size();
				normal_index_map.insert(std::pair<std::size_t, int32_t>(current_index.vertex, normal_model_index));

				normal_model.positions().push_back(current_position);
				normal_model.tex_coords().push_back(current_tex_coord);
				normal_model.normals().push_back(current_normal);
				normal_model.tangents().push_back(glm::vec4(0, 0, 0, 0));
			}

			result->indices().push_back(model_vertex_index);
			normal_model.indices().push_back(normal_model_index);
			index_map.insert(std::pair<std::size_t, int32_t>(model_vertex_index, normal_model_index));
		}

		if (!has_normals_)
		{
			normal_model.calc_normals();

			for (auto i = 0; i < result->positions().size(); i++)
			{
				result->normals().push_back(normal_model.normals()[index_map.at(i)]);
			}
		}

		normal_model.calc_tangents();

		for (auto i = 0; i < result->positions().size(); i++)
		{
			result->tangents().push_back(normal_model.tangents()[index_map.at(i)]);
		}

		return result;
	}

	void ObjModel::load(const std::string &filename)
	{
		std::string::size_type sz;
		std::string line;
		std::ifstream file(filename);

		if (!file.is_open())
			return;

		while (std::getline(file, line))
		{
			const auto tokens = str_split(line, ' ', RemoveEmptyEntries::Yes);

			if (tokens.size() == 0 || tokens[0] == "#")
				continue;

			else if (tokens[0] == "v")
			{
				positions_.push_back(glm::vec4(std::stof(tokens[1], &sz), std::stof(tokens[2], &sz), std::stof(tokens[3], &sz), 1));
			}
			else if (tokens[0] == "vt")
			{
				tex_coords_.push_back(glm::vec4(std::stof(tokens[1], &sz), 1.0f - std::stof(tokens[2], &sz), 0, 0));
			}
			else if (tokens[0] == "vn")
			{
				normals_.push_back(glm::vec4(std::stof(tokens[1], &sz), std::stof(tokens[2], &sz), std::stof(tokens[3], &sz), 0));
			}
			else if (tokens[0] == "f")
			{
				for (auto i = 0; i < tokens.size() - 3; i++)
				{
					indices_.push_back(parse_obj_index(tokens[1]));
					indices_.push_back(parse_obj_index(tokens[2 + i]));
					indices_.push_back(parse_obj_index(tokens[3 + i]));
				}
			}
		}

		file.close();
	}

	OBJIndex ObjModel::parse_obj_index(const std::string &token)
	{
		std::string::size_type sz;
		const auto values = str_split(token, '/', RemoveEmptyEntries::Yes);

		OBJIndex result = { 0 };

		result.vertex = std::stoi(values[0], &sz, 10) - 1;

		if (values.size() > 1)
		{
			if (values[1] != "")
			{
				has_tex_coords_ = true;
				result.text_coord = std::stoi(values[1], &sz, 10) - 1;
			}

			if (values.size() > 2)
			{
				has_normals_ = true;
				result.normal = std::stoi(values[2], &sz, 10) - 1;
			}
		}

		return result;
	}

}
