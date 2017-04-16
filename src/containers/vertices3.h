#pragma once

#include <array>

#include "../geometry/vertex.h"

namespace kiwi {

	class Vertices3
	{
	public:
		Vertices3();
		const std::size_t size;
		void push_back(const Vertex &vertex);
		void clear();
		bool empty() const;
		const Vertex &back() const;
		const Vertex &operator[](std::size_t index) const;

	private:
		std::size_t current_index_;
		std::array<Vertex, 4> vertices_;
	};

}