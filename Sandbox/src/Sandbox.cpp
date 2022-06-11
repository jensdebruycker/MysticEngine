#include <Mystic.h>

#include "imgui/imgui.h"

class ExampleLayer : public Mystic::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPos(0.0f)
	{
		_vertexArray.reset(Mystic::VertexArray::Create());

		float vertices[3*7] = {
			-0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0,
			 0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 1.0,
			 0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0, 1.0
		};

		_vertexBuffer.reset(Mystic::VertexBuffer::Create(vertices, sizeof(vertices)));

		Mystic::BufferLayout layout = {
			{ Mystic::ShaderDataType::Float3, "a_Position"},
			{ Mystic::ShaderDataType::Float4, "a_Color"}
		};
		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2
		};

		_indexBuffer.reset(Mystic::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		_vertexArray->SetIndexBuffer(_indexBuffer);

		std::string vertexSource = R"(
			#version 450
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Color = a_Color;

				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

	void OnUpdate(Mystic::Timestep ts) override
	{
		if (Mystic::Input::IsKeyPressed(MS_KEY_A))
			_cameraPos.x -= _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_D))
			_cameraPos.x += _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_S))
			_cameraPos.y -= _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_W))
			_cameraPos.y += _cameraMoveSpeed * ts;

		if (Mystic::Input::IsKeyPressed(MS_KEY_Q))
			_cameraRot -= _cameraRotationSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_E))
			_cameraRot += _cameraRotationSpeed * ts;

		Mystic::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0 });
		Mystic::RenderCommand::Clear();

		Mystic::Renderer::BeginScene(_camera);

		_camera.SetPosition(_cameraPos);
		_camera.SetRotation(_cameraRot);

		Mystic::Renderer::Submit(_shader, _vertexArray);
		
		Mystic::Renderer::EndScene();
	}

	void OnEvent(Mystic::Event& event) override
	{
	}

private:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:
	std::shared_ptr<Mystic::Shader> _shader;
	std::shared_ptr<Mystic::VertexArray> _vertexArray;
	std::shared_ptr<Mystic::VertexBuffer> _vertexBuffer;
	std::shared_ptr<Mystic::IndexBuffer> _indexBuffer;

	Mystic::OrthographicCamera _camera;
	glm::vec3 _cameraPos;
	float _cameraMoveSpeed = 1.0f;

	float _cameraRot = 0.0f;
	float _cameraRotationSpeed = 1.0f;
public:
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
