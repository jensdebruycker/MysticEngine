#pragma once

#include "Mesh.h"
#include "Material.h"

#include "Mystic/Renderer/Shader.h"

namespace Mystic {

	class Model
	{
	public:
		Model();

		void Move(glm::vec3 amount, float speed);
		void SetPosition(glm::vec3 position);

		void Rotate(glm::vec3 amount, float speed);
		void SetRotation(glm::vec3 rotation);

		void Scale(float amount);
		void SetScale(float scale);

		void Draw(const Ref<Shader> shader);
	public:
		Mesh mesh = Mesh("assets/objects/cube.obj");
		Material material;
	private:
		glm::mat4 _modelMatrix = glm::mat4(1.0f);

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		float _scale = 1.0f;
	};

}