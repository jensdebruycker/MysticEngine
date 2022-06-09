#include "mspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mystic {

	RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI;

}