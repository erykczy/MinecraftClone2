#include "Material.h"
#include "src/app/Debug.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

Material::~Material() {
	glDeleteProgram(m_programId);
}

Material& Material::operator=(const Material& source) {
	if (&source == this) return *this;
	glDeleteProgram(m_programId);
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;
	return *this;
}

Material::Material(Material&& source) noexcept {
	m_programId = source.m_programId;
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;

	source.m_programId = 0;
}

Material& Material::operator=(Material&& source) noexcept {
	if (&source == this) return *this;
	glDeleteProgram(m_programId);

	m_programId = source.m_programId;
	m_vertexPath = source.m_vertexPath;
	m_fragmentPath = source.m_fragmentPath;

	source.m_programId = 0;
	return *this;
}

void Material::use() const {
	glUseProgram(m_programId);
}

unsigned int Material::compileShader(GLenum type, const char* path) {
	std::ifstream file{};
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string code{};
	const char* codeArr{};
	try {
		file.open(path);

		std::stringstream stream{};
		stream << file.rdbuf();

		file.close();

		code = stream.str();
		codeArr = code.c_str();
	}
	catch (std::ifstream::failure) {
		Debug::logger << "Error reading shader file: " << path << Debug::endFatalError;
	}

	unsigned int shader{ glCreateShader(type) };
	glShaderSource(shader, 1, &codeArr, NULL);
	glCompileShader(shader);

	int success{};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		Debug::logger << "Failed to compile shader: " << path << " | error info: " << infoLog << Debug::endFatalError;
	}

	return shader;
}

unsigned int Material::compileAndLinkProgram() {
	unsigned int program{ glCreateProgram() };
	unsigned int vertexShader{ compileShader(GL_VERTEX_SHADER, m_vertexPath) };
	unsigned int fragmentShader{ compileShader(GL_FRAGMENT_SHADER, m_fragmentPath) };

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success{};
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		Debug::logger << "Failed to link program! error info: " << infoLog << Debug::endFatalError;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void Material::setTransformMatricies(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	setMatrix4x4("Model", modelMatrix);
	setMatrix4x4("View", viewMatrix);
	setMatrix4x4("Projection", projectionMatrix);
}

void Material::setMatrix4x4(std::string_view uniformName, const glm::mat4& matrix) {
	glProgramUniformMatrix4fv(m_programId, findUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Material::setVector3(std::string_view uniformName, const glm::vec3& vec) {
	glProgramUniform3fv(m_programId, findUniformLocation(uniformName), 1, glm::value_ptr(vec));
}

void Material::setVector4(std::string_view uniformName, const glm::vec4& vec)
{
	glProgramUniform4fv(m_programId, findUniformLocation(uniformName), 1, glm::value_ptr(vec));
}

void Material::setFloat(std::string_view uniformName, float value)
{
	glProgramUniform1f(m_programId, findUniformLocation(uniformName), value);
}

void Material::setInt(std::string_view uniformName, int value)
{
	glProgramUniform1i(m_programId, findUniformLocation(uniformName), value);
}

void Material::setTextureUnit(std::string_view uniformName, int textureUnit) {
	glProgramUniform1i(m_programId, findUniformLocation(uniformName), textureUnit);
}

int Material::findUniformLocation(std::string_view name) const {
	return glGetUniformLocation(m_programId, name.data());
}
