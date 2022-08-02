#pragma once

#include <iostream>

#include "Vertex.h"

#include "Mystic/Renderer/Buffer.h"
#include "Mystic/Renderer/VertexArray.h"

#include "Mystic/Renderer/Shader.h"

namespace Mystic {

	class Mesh
	{
	public:
		Mesh(const std::string& filepath);

		void Draw(Ref<Shader> shader, glm::mat4 modelMatrix);
	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;

		Ref<VertexArray> va;
		Ref<VertexBuffer> vb;
		Ref<IndexBuffer> ib;
	private:
		void loadMesh(const std::string& filepath);
		void push_vertex_data(int i, int n, int t);
	};

}