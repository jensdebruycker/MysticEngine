#include "mspch.h"
#include "Texture.h"

#include "Mystic/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mystic {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		MS_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

}