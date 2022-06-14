#include <Mystic.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Mystic::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPos(0.0f), _trianglePosition(0.0f)
	{
		_vertexArray.reset(Mystic::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		_vertexBuffer.reset(Mystic::VertexBuffer::Create(vertices, sizeof(vertices)));

		Mystic::BufferLayout layout = {
			{ Mystic::ShaderDataType::Float3, "a_Position"},
			{ Mystic::ShaderDataType::Float2, "a_TexCoord"}
		};
		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		_indexBuffer.reset(Mystic::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		_vertexArray->SetIndexBuffer(_indexBuffer);

		std::string flatColorVertexSrc = R"(
			#version 450
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 450
			
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;
			
			void main()
			{
				color = u_Color;
			}
		)";

		_flatColorShader.reset(Mystic::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));

		std::string texVertexSrc = R"(
			#version 450
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string texFragmentSrc= R"(
			#version 450
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		_texShader.reset(Mystic::Shader::Create(texVertexSrc, texFragmentSrc));

		_texture = Mystic::Texture2D::Create("assets/textures/checkerboard.png");
		_texShader->Bind();
		_texShader->UploadInt("u_Texture", 0);
	}

	void OnUpdate(Mystic::Timestep ts) override
	{
		if (Mystic::Input::IsKeyPressed(MS_KEY_LEFT))
			_cameraPos.x -= _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_RIGHT))
			_cameraPos.x += _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_DOWN))
			_cameraPos.y -= _cameraMoveSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_UP))
			_cameraPos.y += _cameraMoveSpeed * ts;

		if (Mystic::Input::IsKeyPressed(MS_KEY_Q))
			_cameraRot -= _cameraRotationSpeed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_E))
			_cameraRot += _cameraRotationSpeed * ts;

		if (Mystic::Input::IsKeyPressed(MS_KEY_A))
			_trianglePosition.x -= _speed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_D))
			_trianglePosition.x += _speed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_S))
			_trianglePosition.y -= _speed * ts;
		if (Mystic::Input::IsKeyPressed(MS_KEY_W))
			_trianglePosition.y += _speed * ts;

		Mystic::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0 });
		Mystic::RenderCommand::Clear();

		_camera.SetPosition(_cameraPos);
		_camera.SetRotation(_cameraRot);

		Mystic::Renderer::BeginScene(_camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		_flatColorShader->Bind();
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				if (x % 2 == y % 2)
					_flatColorShader->UploadFloat4("u_Color", blueColor);
				else
					_flatColorShader->UploadFloat4("u_Color", redColor);

				Mystic::Renderer::Submit(_flatColorShader, _vertexArray, transform);
			}
		}

		_texture->Bind();
		Mystic::Renderer::Submit(_texShader, _vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		Mystic::Renderer::EndScene();
	}

	void OnEvent(Mystic::Event& event) override
	{
	}

private:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:
	Mystic::Ref<Mystic::Shader> _flatColorShader, _texShader;
	Mystic::Ref<Mystic::VertexArray> _vertexArray;
	Mystic::Ref<Mystic::VertexBuffer> _vertexBuffer;
	Mystic::Ref<Mystic::IndexBuffer> _indexBuffer;

	Mystic::Ref<Mystic::Texture2D> _texture;

	Mystic::OrthographicCamera _camera;
	glm::vec3 _cameraPos;
	float _cameraMoveSpeed = 2.0f;

	float _cameraRot = 0.0f;
	float _cameraRotationSpeed = 30.0f;

	glm::vec3 _trianglePosition;
	float _speed = 1.0f;

public:
		void OnImGuiRender() override
		{
			/*static float f = 0.0f;
			static int counter = 0;*/

			ImGui::Begin("Hello, world!");

			/*ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window", &show_demo_window);
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);

			if (ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);*/

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
