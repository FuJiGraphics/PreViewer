#include <pch.h>
#include "Shader.h"
#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGL_Shader.h>

namespace PreViewer 
{
	Shader* Shader::Create(const ShaderPaths& paths)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return new OpenGLShader(paths);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

	void ShaderManager::Add(const std::string& name, const PrePtr<Shader>& shader)
	{
		// NR_CORE_ASSERT(!this->Exist(name), "Shader data already exists! ");
		m_Shaders.insert(std::make_pair(name, shader));
	}

	bool ShaderManager::Exist(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}


}