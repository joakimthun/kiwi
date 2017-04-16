#include "indexed_model.h"

#include "../util.h"

namespace kiwi {

	std::vector<Vec4> &IndexedModel::positions()
	{
		return positions_;
	}

	std::vector<Vec4> &IndexedModel::tex_coords()
	{
		return tex_coords_;
	}

	std::vector<Vec4> &IndexedModel::normals()
	{
		return normals_;
	}

	std::vector<std::size_t> &IndexedModel::indices()
	{
		return indices_;
	}

	std::vector<Vec4> &IndexedModel::tangents()
	{
		return tangents_;
	}

	void IndexedModel::calc_normals()
	{
		for (auto i = 0; i < indices_.size(); i += 3)
		{
			const auto i0 = indices_[i];
			const auto i1 = indices_[i + 1];
			const auto i2 = indices_[i + 2];

			const auto v1 = positions_[i1] - positions_[i0];
			const auto v2 = positions_[i2] - positions_[i0];

			const auto normal = v1.cross(v2).normalize();

			normals_[i0] = normals_[i0] + normal;
			normals_[i1] = normals_[i1] + normal;
			normals_[i2] = normals_[i2] + normal;
		}

		for (auto i = 0; i < normals_.size(); i++)
			normals_[i] = normals_[i].normalize();
	}

	void IndexedModel::calc_tangents()
	{
		for (auto i = 0; i < indices_.size(); i += 3)
		{
			const auto i0 = indices_[i];
			const auto i1 = indices_[i + 1];
			const auto i2 = indices_[i + 2];

			const auto edge_1 = positions_[i1] - positions_[i0];
			const auto edge_2 = positions_[i2] - positions_[i0];

			const auto delta_u1 = tex_coords_[i1].x - tex_coords_[i0].x;
			const auto delta_v1 = tex_coords_[i1].y - tex_coords_[i0].y;
			const auto delta_u2 = tex_coords_[i2].x - tex_coords_[i0].x;
			const auto delta_v2 = tex_coords_[i2].y - tex_coords_[i0].y;

			const auto dividend = (delta_u1 * delta_v2 - delta_u2 * delta_v1);
			const auto f = dividend == 0 ? 0.0f : 1.0f / dividend;

			const auto tangent = Vec4(
				f * (delta_v2 * edge_1.x - delta_v1 * edge_2.x),
				f * (delta_v2 * edge_1.y - delta_v1 * edge_2.y),
				f * (delta_v2 * edge_1.z - delta_v1 * edge_2.z),
				0);

			tangents_[i0] = tangents_[i0] + tangent;
			tangents_[i1] = tangents_[i1] + tangent;
			tangents_[i2] = tangents_[i2] + tangent;
		}

		for (auto i = 0; i < tangents_.size(); i++)
			tangents_[i] = tangents_[i].normalize();
	}

}
