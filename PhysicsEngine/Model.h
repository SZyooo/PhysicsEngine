#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include <map>
namespace YoungEngine::Geometry
{
	class Vec3D;
};
class aiScene;
class aiNode;
class aiMesh;
class aiMaterial;
namespace YoungEngine::Model
{
	class Model
	{
		std::vector<Mesh> meshs;
		std::map<std::string,Texture> diffuses;
		std::map<std::string, Texture> speculars;
		std::map<std::string, Texture> ambients;
		YoungEngine::Geometry::Transform transform;
		void processNode(const aiScene* scene, aiNode* node);
		void processMesh(const aiScene*, aiMesh* mesh);
		void processMaterial(const aiMaterial* mat, Mesh& mesh);
	public:
		Model(const char* file);

		glm::mat4 getTransform() const;
		void draw(unsigned int vao, unsigned int program);
	};
};