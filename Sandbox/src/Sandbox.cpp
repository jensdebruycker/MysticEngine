#include <Mystic.h>

#include "imgui/imgui.h"

#include "glad/glad.h"

class ExampleLayer : public Mystic::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		float vertices[] = {
			 0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};

		_vertexBuffer.reset(Mystic::VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 1
		};
		_indexBuffer.reset(Mystic::IndexBuffer::Create(indices, 18));

		std::string vertexSource = R"(
			#version 450
			
			layout(location = 0) in vec4 _position;
			
			void main()
			{
				gl_Position = _position;
			}
		)";

		std::string fragmentSource = R"(
			#version 450
			
			layout(location = 0) out vec4 _color;
			
			void main()
			{
				_color = vec4(1.0, 0.0, 1.0, 1.0);
			}
		)";

		_shader.reset(Mystic::Shader::Create(vertexSource, fragmentSource));
	}

	void OnUpdate() override
	{
		glClearColor(1.0f, 0.65f, 0.0f, 1.0);
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
