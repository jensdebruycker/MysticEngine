#include "mspch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Mystic {

	static GLenum ShaderDataTypeToOpenGLBaseType(Mystic::ShaderDataType type)
	{
		switch (type)
		{
			case Mystic::ShaderDataType::Float: return GL_FLOAT;
			case Mystic::ShaderDataType::Float2: return GL_FLOAT;
			case Mystic::ShaderDataType::Float3: return GL_FLOAT;
			case Mystic::ShaderDataType::Float4: return GL_FLOAT;
			case Mystic::ShaderDataType::Mat3: return GL_FLOAT;
			case Mystic::ShaderDataType::Mat4: return GL_FLOAT;
			case Mystic::ShaderDataType::Int: return GL_INT;
			case Mystic::ShaderDataType::Int2: return GL_INT;
			case Mystic::ShaderDataType::Int3: return GL_INT;
			case Mystic::ShaderDataType::Int4: return GL_INT;
			case Mystic::ShaderDataType::Bool: return GL_BOOL;
		}

		MS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(_rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		MS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!")

		glBindVertexArray(_rendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);

			index++;
		}

		_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(_rendererID);
		indexBuffer->Bind();

		_indexBuffer = indexBuffer;
	}

}
