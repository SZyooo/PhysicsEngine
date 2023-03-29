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
		std::string model_path;
		void load();
	public:
		Model(const char* file);
		Model(const Model& m);
		Model& operator=(const Model& m);
		Model(Model&& m) noexcept;
		Model& operator=(Model&& m) noexcept;
		glm::mat4 getTransform() const;
		void draw(unsigned int program);

		void translate(const Geometry::Vec3D& move);
		void rotate(const Geometry::Vec3D& eularAngle, Geometry::Transform::ROTATEORDER order);
		void rotate(const glm::quat& q);
		void scale(const Geometry::Vec3D& scale);
		~Model();
	};
};