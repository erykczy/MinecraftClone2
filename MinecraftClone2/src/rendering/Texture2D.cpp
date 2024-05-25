#pragma once
#include "Texture2D.h"
#include "src/app/Debug.h"
#include <glad/glad.h>
#include <libraries/stb_image.h>


Texture2D::Texture2D(const char* path, Format format) : m_path{ path }
{
	// create texture
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	// setup texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load texture
	int nrChannels;
	unsigned char* data{ stbi_load(path, &m_width, &m_height, &nrChannels, 0) };
	if (!data) Debug::logger << "Failed to load texture" << path << Debug::endError;

	// set data
	auto texFormat = format == rgb ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, texFormat, m_width, m_height, 0, texFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::bindToTextureUnit(int textureUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
