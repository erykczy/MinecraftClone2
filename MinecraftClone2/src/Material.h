#pragma once
#include <glm/glm.hpp>
#include <string_view>
using GLenum = unsigned int;

class Material final {
public:
	Material(const char* vertexPath, const char* fragmentPath) : m_vertexPath{ vertexPath }, m_fragmentPath{ fragmentPath } {
		m_programId = compileAndLinkProgram();
	}

	~Material();
	Material(const Material& source) : Material(source.m_vertexPath, source.m_fragmentPath) {}
	Material& operator=(const Material& source);
	Material(Material&& source) noexcept;
	Material& operator=(Material&& source) noexcept;

	void setTransformMatricies(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void setMatrix4x4(std::string_view uniformName, const glm::mat4& matrix);
	void setVector3(std::string_view uniformName, const glm::vec3& vec);
	void setVector4(std::string_view uniformName, const glm::vec4& vec);
	void setFloat(std::string_view uniformName, float value);
	void setInt(std::string_view uniformName, int value);

	void use() const;

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};

	unsigned int compileShader(GLenum type, const char* path);
	unsigned int compileAndLinkProgram();

	int findUniformLocation(std::string_view name) const;
};