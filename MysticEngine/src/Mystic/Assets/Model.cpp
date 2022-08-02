#include "mspch.h"

#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Mystic {

	Model::Model()
	{
	}

	void Model::Move(glm::vec3 amount, float speed)
	{
		_position += amount * speed;
		glm::translate(_modelMatrix, _position);
	}

	void Model::SetPosition(glm::vec3 position)
	{
		_position = position;
		glm::translate(_modelMatrix, _position);
	}

	void Model::Rotate(glm::vec3 amount, float speed)
	{
	}

	void Model::SetRotation(glm::vec3 rotation)
	{
	}

	void Model::Scale(float amount)
	{
		_scale += amount;
		glm::scale(_modelMatrix, glm::vec3(_scale, _scale, _scale));
	}

	void Model::SetScale(float scale)
	{
		_scale = scale;
		glm::scale(_modelMatrix, glm::vec3(_scale, _scale, _scale));
	}

	void Model::Draw(const Ref<Shader> shader)
	{
		shader->UploadFloat3("u_Color", material.color);
		shader->UploadFloat3("u_LightColor", material.lightColor);
		shader->UploadFloat("u_Shininess", material.shininess);

		mesh.Draw(shader, _modelMatrix);
	}

}