#pragma once

#include <glm/glm.hpp>

namespace Mystic {

	struct Material
	{
		glm::vec3 color = { 0.85f, 0.85f, 0.8f };

		glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
		float shininess = 50.0f;
	};

}