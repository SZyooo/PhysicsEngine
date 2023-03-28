#include "Texture.h"
#include <stb_image.h>
#include <GL/glew.h>
YoungEngine::Model::Texture::Texture(std::string& path, TextureType type, GLenum specifiedInternalFormat, GLenum specifiedFormat, int level)
	:path(path),type(type),level(level),valid(true)
{
	
	int channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* img = stbi_load(path.c_str(), &wid, &hei, &channel, 0);
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	GLenum internalformat;
	GLenum format;
	if (specifiedInternalFormat != 0)
	{
		internalformat = specifiedInternalFormat;
	}
	else
	{
		if (channel == 1)
		{
			internalformat = GL_R32F;
			format = GL_RED;
		}
		else if (channel == 3)
		{
			internalformat = GL_RGB32F;
			format = GL_RGB;
		}
		else
		{
			internalformat = GL_RGBA32F;
			format = GL_RGBA;
		}
	}
	if (specifiedFormat != 0)
	{
		format = specifiedFormat;
	}
	glTextureStorage2D(id, level, internalformat, wid, hei);
	glTextureSubImage2D(id, 0, 0, 0, wid, hei, format, GL_UNSIGNED_BYTE, img);
	stbi_image_free(img);
	glGenerateTextureMipmap(id);
}

unsigned int YoungEngine::Model::Texture::textureID() const
{
	return id;
}

YoungEngine::Model::Texture::TextureType YoungEngine::Model::Texture::textureType() const
{
	return type;
}

std::string YoungEngine::Model::Texture::texturePath() const
{
	return path;
}

void YoungEngine::Model::Texture::free()
{
	glDeleteTextures(1,&id);
	valid = false;
}

void YoungEngine::Model::Texture::move(Texture& t)
{
	t.path = path;
	t.type = type;
	t.id = id;
	t.wid = wid;
	t.hei = hei;
	id = 0;
	valid = false;
}

int YoungEngine::Model::Texture::texturewWidth() const
{
	return wid;
}

int YoungEngine::Model::Texture::textureHeight() const
{
	return hei;
}

int YoungEngine::Model::Texture::textureLevel() const
{
	return level;
}

bool YoungEngine::Model::Texture::isValid() const
{
	return valid;
}

