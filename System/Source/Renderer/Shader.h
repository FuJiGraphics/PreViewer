#pragma once

#include <Core/Core.h>

namespace PreViewer {

	struct ShaderPaths
	{
		std::string VertPath;
		std::string FragPath;
	};

	class Shader
	{
	protected:
		explicit Shader() = default;
	public:
		virtual ~Shader() = default;

	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetInt(const std::string& name, const unsigned int& int1) = 0;
		virtual void SetFloat(const std::string& name, const float& float1) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& float4) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& mat4) = 0;

		static Shader* Create(const ShaderPaths& paths);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderManager
	{
	public:
		void Add(const std::string& name, const PrePtr<Shader>& shader);
		bool Exist(const std::string& name) const;

		inline PrePtr<Shader>& Get(const std::string& name) {
			return m_Shaders.at(name);
		}
		inline const PrePtr<Shader>& Get(const std::string& name) const {
			return m_Shaders.at(name);
		}
		inline PrePtr<Shader>& operator[](const std::string& name) {
			return m_Shaders[name];
		}

	private:
		std::unordered_map< std::string, PrePtr<Shader> > m_Shaders;
	};
} // namespace Normal