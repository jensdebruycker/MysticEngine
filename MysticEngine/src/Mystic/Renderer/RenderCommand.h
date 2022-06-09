#pragma once

#include "RendererAPI.h"

namespace Mystic {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			_rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			_rendererAPI->DrawIndexed(vertexArray);
		}
	public:
		static RendererAPI* _rendererAPI;
	};

}