#include <iostream>

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window.h"
#include "renderer.h"
#include "vertex.h"

using namespace kiwi;

// TODO: Use a real timer...
const float dt = 0.0016f;

int main(int argc, char* argv[])
{
	Window window(800, 600);
	window.open();

	Renderer renderer(&window);
	renderer.clear(0x00, 0x00, 0x00);

	Vertex min_y(
			-1, -1, 0, 1,
			1, 0, 0, 0);

	Vertex mid_y(
		0, 1, 0, 1,
		0, 1, 0, 0);

	Vertex max_y(
		1, -1, 0, 1,
		0, 0, 1, 0);

	glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.f / 600.f, -0.1f, 1000.0f);
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
	float rotation_v = 0.0f;

	MSG msg = { 0 };
	while (1)
	{
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		renderer.clear(0x00, 0x00, 0x00);

		rotation_v += dt * 2.5f;
		const auto rotation = glm::rotate(translation, rotation_v, glm::vec3(0.0f, 1.0f, 0.0f));
		const auto transform = projection * translation * rotation;

		renderer.fill_triangle(min_y.transform(transform), mid_y.transform(transform), max_y.transform(transform));

		window.update();
	}

	return 0;
}