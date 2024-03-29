#pragma once

#include "RenderCommand.h"
#include "Mystic/Assets/Camera.h"
#include "Shader.h"

namespace Mystic {

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(Camera2D& camera);
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* _sceneData;
	};

}