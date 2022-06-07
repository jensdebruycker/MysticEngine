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
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
			
		}

		BufferElement() {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3: return 3 * 3;
				case ShaderDataType::Mat4: return 4 * 4;
				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;
				case ShaderDataType::Bool: return 1;
			}

			MS_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: _elements(elements) 
		{
			CalculateOffsetsAndStride();
		}

		BufferLayout() {}

		inline uint32_t GetStride() const { return _stride; }
		inline const std::vector<BufferElement>& GetElements() const { return _elements; };

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			_stride = 0;
			for (auto& element : _elements)
			{
				element.Offset = offset;
				offset += element.Size;
				_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> _elements;
		uint32_t _stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

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