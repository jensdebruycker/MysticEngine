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

		void Draw(Ref<Shader> shader);
	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		Ref<VertexArray> va;
		Ref<VertexBuffer> vb;
		Ref<IndexBuffer> ib;
	private:
		void loadMesh(const std::string& filepath);
	};

}