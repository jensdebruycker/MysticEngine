#pragma once

#include "glm/glm.hpp"

namespace Mystic {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadInt(const std::string& name, int value) = 0;
		virtual void UploadFloat(const std::string& name, float value) = 0;
		virtual void UploadFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void UploadFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void UploadFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void UploadMat4(const std::string& name, const glm::mat4& value) = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}