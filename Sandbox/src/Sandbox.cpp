#include <Mystic.h>

#include "imgui/imgui.h"

#include "glad/glad.h"

class ExampleLayer : public Mystic::Layer
{
public:
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

	ExampleLayer() : Layer("Example")
	{
		

		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		float vertices[3*7] = {
			-0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0,
			 0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 1.0,
			 0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0, 1.0
		};

		_vertexBuffer.reset(Mystic::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			Mystic::BufferLayout layout = {
				{ Mystic::ShaderDataType::Float3, "a_Position"},
				{ Mystic::ShaderDataType::Float4, "a_Color"}
			};
			_vertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = _vertexBuffer->GetLayout();
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

		unsigned int indices[] = {
			0, 1, 2
		};
		_indexBuffer.reset(Mystic::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		std::string vertexSource = R"(
			#version 450
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Color = a_Color;

				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 450
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		_shader.reset(Mystic::Shader::Create(vertexSource, fragmentSource));
	}

	void OnUpdate() override
	{
		glClearColor(0.15f, 0.15f, 0.15f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		_shader->Bind();
		glBindVertexArray(_vertexArray);
		glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OnImGuiRender() override
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");

		ImGui::Text("This is some useful text.");
		ImGui::Checkbox("Demo Window", &show_demo_window);
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);

		if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void OnEvent(Mystic::Event& event) override
	{

	}
private:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:
	unsigned int _vertexArray;
	//VertexArray _vertexArray;
	std::unique_ptr<Mystic::Shader> _shader;
	std::unique_ptr<Mystic::VertexBuffer> _vertexBuffer;
	std::unique_ptr<Mystic::IndexBuffer> _indexBuffer;
};

class Sandbox : public Mystic::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mystic::Application* Mystic::CreateApplication()
{
	return new Sandbox;
}
