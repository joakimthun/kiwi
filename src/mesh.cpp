#include "mesh.h"

#include "models/obj.h"

namespace kiwi {

	Mesh::Mesh(const std::string &filename)
	{
		model_ = models::Obj::from_file(filename);

		for (auto i = 0; i < model_->positions().size(); i++)
		{
			vertices_.push_back(Vertex(model_->positions()[i], model_->tex_coords()[i]));
		}
	}

	const Vertex &Mesh::get_vertex(std::size_t i) const
	{
		return vertices_[i];
	}

	std::size_t Mesh::get_index(std::size_t i) const
	{
		return model_->indices()[i];
	}

	std::size_t Mesh::num_indices() const
	{
		return model_->indices().size();
	}

}
