#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Struct to save the shader
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_Filepath;
	unsigned int m_RenderedID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader();
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// void setShader(const std::string& filepath)

	// Set uniforms
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetTransformMatrix(const std::string& name, glm::mat4 transform);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};
