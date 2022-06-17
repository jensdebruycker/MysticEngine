#pragma once

#include "Mystic/Renderer/Shader.h"
#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace Mystic {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadInt(const std::string& name, int value) override;
		virtual void UploadFloat(const std::string& name, float value) override;
		virtual void UploadFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void UploadFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void UploadFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void UploadMat4(const std::string& name, const glm::mat4& value) override;
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t _rendererID;
	};

}