#include "src/Material.h"
#include "src/Debug.h"
#include <glad/glad.h>
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