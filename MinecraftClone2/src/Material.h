#pragma once
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

	void use() const;

private:
	unsigned int m_programId{};
	const char* m_vertexPath{};
	const char* m_fragmentPath{};

	unsigned int compileShader(GLenum type, const char* path);
	unsigned int compileAndLinkProgram();
};