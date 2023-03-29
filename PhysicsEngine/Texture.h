#pragma once
#include <string>
#include <GL/glew.h>
namespace YoungEngine::Model
{
	
	class Texture
	{
	public:
		enum class TextureType
		{
			DIFFUSE, SPECULAR, AMBIENT
		};
	private:
		std::string path;
		unsigned int id;
		TextureType type;
		int wid, hei;
		int level;
		bool valid;
	public:
		Texture() {};
		Texture& operator=(const Texture& t) = delete;
		Texture(const Texture& t) = delete;
		Texture(Texture&& t)noexcept;
		Texture& operator=(Texture&& t);
		Texture(const std::string& path, TextureType type,GLenum specifiedInternalFormat = 0,GLenum specifiedFormat = 0, int level = 1);
		unsigned int textureID() const;
		TextureType textureType() const;
		std::string texturePath()const;
		void free();
		void move(Texture& t);
		int texturewWidth() const;
		int textureHeight() const;
		int textureLevel() const;
		bool isValid() const;
	};
};