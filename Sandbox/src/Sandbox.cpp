#include <Mystic.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Mystic::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), _mesh("assets/objects/monkey.obj")
	{
		_camera.SetSmoothing(0.8f);

		_vertexArray.reset(Mystic::VertexArray::Create());

		/*float vertices[] = {
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

		_indexBuffer.reset(Mystic::IndexBuffer::Create(indices, sizeof(indices)));

		_vertexArray->SetIndexBuffer(_indexBuffer);*/

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
		_lightShader.reset(Mystic::Shader::Create("assets/shaders/light.glsl"));

		_model.mesh = Mystic::Mesh("assets/objects/torus.obj");
		_model.material = _material;

		_plane.mesh = Mystic::Mesh("assets/objects/plane.obj");
		_plane.material = _material;

		_texShader.reset(Mystic::Shader::Create("assets/shaders/texture.glsl"));
		_texture = Mystic::Texture2D::Create("assets/textures/wood.png");
		_texShader->Bind();
		_texShader->UploadInt("u_Texture", 0);

		/*_texShader.reset(Mystic::Shader::Create("assets/shaders/texture.glsl"));

		_texture = Mystic::Texture2D::Create("assets/textures/checkerboard.png");
		_heartTexture = Mystic::Texture2D::Create("assets/textures/heart.png");

		_texShader->Bind();
		_texShader->UploadInt("u_Texture", 0);*/
	}

	void OnUpdate(Mystic::Timestep ts) override
	{
		//_camera.AddYawPitchRoll(glm::vec3(-Mystic::Input::GetMouseOffsetX() * 0.1, Mystic::Input::GetMouseOffsetY() * 0.1, 0.0f));
		_camera.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));

		if (Mystic::Input::IsKeyPressed(MS_KEY_A))
			_camera.MoveLeft(ts);
		if (Mystic::Input::IsKeyPressed(MS_KEY_D))
			_camera.MoveRight(ts);
		if (Mystic::Input::IsKeyPressed(MS_KEY_S))
			_camera.MoveBackward(ts);
		if (Mystic::Input::IsKeyPressed(MS_KEY_W))
			_camera.MoveForward(ts);
		if (Mystic::Input::IsKeyPressed(MS_KEY_LEFT_CONTROL))
			_camera.MoveDown(ts);
		if (Mystic::Input::IsKeyPressed(MS_KEY_LEFT_SHIFT))
			_camera.MoveUp(ts);

		Mystic::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0 });
		Mystic::RenderCommand::Clear();

		Mystic::Renderer::BeginScene(_camera);

		_camera.Update(ts);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		glm::vec4 whiteColor(0.84f, 0.85f, 0.8f, 1.0f);

		glm::vec3 brownColor(0.72f, 0.25f, 0.15f);
		glm::vec3 lightPos(2.0f, 10.0f, 5.0f);

		/*_flatColorShader->Bind();
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

		_heartTexture->Bind();
		Mystic::Renderer::Submit(_texShader, _vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));*/

		/*_lightShader->Bind();
		_lightShader->UploadFloat4("u_Color", brownColor);
		_lightShader->UploadFloat3("u_LightPos", lightPos);
		_lightShader->UploadFloat3("u_LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		_lightShader->UploadFloat3("u_CameraPos", _camera.GetPosition());
		_mesh.Draw(_lightShader, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

		_flatColorShader->Bind();
		_flatColorShader->UploadFloat4("u_Color", whiteColor);
		_mesh.Draw(_flatColorShader, glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)));*/

		_texture->Bind();
		

		_lightShader->UploadFloat3("u_LightPos", lightPos);
		_lightShader->UploadFloat3("u_CameraPos", _camera.GetPosition());
		_lightShader->UploadFloat("u_Gamma", _gamma);
		_material.color = brownColor;
		_model.material = _material;
		_model.Draw(_lightShader);
		
		Mystic::Renderer::EndScene();
	}

	void OnEvent(Mystic::Event& event) override
	{
		
	}

private:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:
	Mystic::Ref<Mystic::Shader> _flatColorShader, _texShader, _lightShader;
	Mystic::Ref<Mystic::VertexArray> _vertexArray;
	Mystic::Ref<Mystic::VertexBuffer> _vertexBuffer;
	Mystic::Ref<Mystic::IndexBuffer> _indexBuffer;

	Mystic::Ref<Mystic::Texture2D> _texture, _heartTexture;

	Mystic::Camera _camera;

	Mystic::Mesh _mesh;
	Mystic::Material _material;
	Mystic::Model _model;
	Mystic::Model _plane;

	float _gamma = 0.9f;
public:
	void OnImGuiRender() override
	{
		ImGui::Begin("Hello, world!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SliderFloat("Gamma", &_gamma, 0.01f, 2.0f);
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
