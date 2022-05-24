#pragma once

namespace Mystic {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Mystic::ShaderDataType::Float:  return 4;
			case Mystic::ShaderDataType::Float2: return 4 * 2;
			case Mystic::ShaderDataType::Float3: return 4 * 3;
			case Mystic::ShaderDataType::Float4: return 4 * 4;
			case Mystic::ShaderDataType::Mat3:   return 4 * 3 * 3;
			case Mystic::ShaderDataType::Mat4:   return 4 * 3 * 4;
			case Mystic::ShaderDataType::Int:    return 4;
			case Mystic::ShaderDataType::Int2:   return 4 * 2;
			case Mystic::ShaderDataType::Int3:   return 4 * 3;
			case Mystic::ShaderDataType::Int4:   return 4 * 4;
			case Mystic::ShaderDataType::Bool:   return 1;
		}

		MS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;

		BufferElement(ShaderDataType type, const std::string& name)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{
			
		}
	};

	class BufferLayout
	{
	public:


		inline const std::vector<BufferElement>& GetElements() const { return _elements; };
	private:
		std::vector<BufferElement> _elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* Create(unsigned int* indices, unsigned int size);
	};

}