#pragma once

#include "Mystic/Renderer/Buffer.h"

namespace Mystic {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return _layout; }
		virtual void SetLayout(const BufferLayout& layout) override { _layout = layout; }
	private:
		unsigned int _rendererID;
		BufferLayout _layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual unsigned int GetCount() const { return _count; }
	private:
		unsigned int _rendererID;
		unsigned int _count;
	};

}