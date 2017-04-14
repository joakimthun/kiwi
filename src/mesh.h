#pragma once

#include <vector>
#include <string>
#include <memory>

#include "vertex.h"
#include "models/indexed_model.h"

namespace kiwi {

	class Mesh
	{
	public:
		Mesh(const std::string &filename);

		const Vertex &get_vertex(std::size_t i) const;
		std::size_t get_index(std::size_t i) const;
		std::size_t num_indices() const;


	private:
		std::vector<Vertex> vertices_;
		std::unique_ptr<models::IndexedModel> model_;
	};

}
