#include "obj.h"

#include <iostream>
#include <fstream>

#include "../util.h"

namespace kiwi {
	namespace models {

		Obj::Obj(const std::string &filename)
			:
			has_tex_coords_(false),
			has_normals_(false)
		{
			load(filename);
		}

		void Obj::load(const std::string &filename)
		{
			std::string::size_type sz;
			std::string line;
			std::ifstream file(filename);

			if (!file.is_open())
				return;

			while (getline(file, line))
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

		OBJIndex Obj::parse_obj_index(const std::string &token)
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
}
