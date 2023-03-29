#include "Model.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "Vec3D.h"
#include "Vertex.h"
#include "Debug.h"
namespace YoungEngine::Model
{

	glm::mat4 Model::getTransform() const
	{
		return transform.getTransformMatrix();
	}
	void Model::draw(unsigned int program)
	{
		for (auto& mesh : meshs)
		{
			mesh.draw(program);
		}
	}
	void Model::translate(const Geometry::Vec3D& move)
	{
		transform.translate(move);
	}
	void Model::rotate(const Geometry::Vec3D& eularAngle, Geometry::Transform::ROTATEORDER order)
	{
		transform.rotate(eularAngle, order);
	}
	void Model::rotate(const glm::quat& q)
	{
		transform.rotate(q);
	}
	void Model::scale(const Geometry::Vec3D& s)
	{
		transform.scale(s);
	}
	Model::Model(const char* file)
		:model_path(file)
	{
		size_t idx= std::string::npos;
		while ((idx = model_path.find("\\")) != std::string::npos)
		{
			model_path.replace(idx, 1, "/");
		}
		load();
	}

	Model::Model(const Model& m)
		:model_path(m.model_path)
	{
		size_t idx = std::string::npos;
		while (idx = model_path.find("\\") != std::string::npos)
		{
			model_path.replace(idx, idx + 2, "/");
		}
		load();
	}

	Model& Model::operator=(const Model& m)
	{
		model_path = m.model_path;
		load();
		return *this;
	}

	Model::Model(Model&& m)noexcept
	{
		meshs.swap(m.meshs);
		diffuses.swap(m.diffuses);
		speculars.swap(m.speculars);
		ambients.swap(m.ambients);
		transform = m.transform;
		model_path = m.model_path;
	}

	Model& Model::operator=(Model&& m)noexcept
	{
		meshs.swap(m.meshs);
		diffuses.swap(m.diffuses);
		speculars.swap(m.speculars);
		ambients.swap(m.ambients);
		transform = m.transform;
		model_path = m.model_path;
		return *this;
	}

	void Model::processNode(const aiScene* scene, aiNode* node)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			processMesh(scene,scene->mMeshes[node->mMeshes[i]]);
		}
		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(scene, node->mChildren[i]);
		}
	}
	Geometry::Vec3D fromaiVector3D(const aiVector3D& v)
	{
		return { v.x,v.y,v.z };
	}
	void Model::processMesh(const aiScene* scene, aiMesh* mesh){
		std::vector<YoungEngine::Geometry::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::string name;
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			auto v = mesh->mVertices[i];
			auto n = mesh->mNormals[i];
			name = mesh->mName.C_Str();
			Geometry::Vec3D vertex = fromaiVector3D(v);
			Geometry::Vec3D norm = fromaiVector3D(n);
			unsigned int UVchannel = mesh->GetNumUVChannels();
			float U, V;
			if (UVchannel == 0)
			{
				U = V = 0;
			}
			else
			{
				auto uv = mesh->mTextureCoords[0][i];
				U = uv.x;
				V = uv.y;
			}
			Geometry::Vertex vert;
			vert.position = vertex;
			vert.norm = norm;
			vert.u = U;
			vert.v = V;
			vertices.push_back(vert);
		}
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		meshs.emplace(meshs.end(), name, vertices, indices);
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		processMaterial(mat, *meshs.rbegin());
	}

	void Model::processMaterial(const aiMaterial* mat, Mesh& mesh)
	{
		std::vector<unsigned int> diff;
		std::vector<unsigned int> spec;
		std::vector<unsigned int> ambt;

		int diffuseCount = mat->GetTextureCount(aiTextureType_DIFFUSE);
		int ambientCount = mat->GetTextureCount(aiTextureType_AMBIENT);
		int specularCount = mat->GetTextureCount(aiTextureType_SPECULAR);
		int baseCount = mat->GetTextureCount(aiTextureType_BASE_COLOR);
		for (int j = 0; j < diffuseCount; j++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, j, &path);
			std::string stdstr(path.C_Str());
			if (stdstr[0] != '/')
			{
				stdstr.insert(0, "/");
			}
			size_t x= model_path.find_last_of('/');
			stdstr = model_path.substr(0, x) + stdstr;
			if (diffuses.find(stdstr) == diffuses.end())
			{
				diffuses.emplace(std::make_pair(stdstr, Texture(stdstr, Texture::TextureType::DIFFUSE)));
			}
			diff.push_back(diffuses[stdstr].textureID());
		}
		for (int j = 0; j < ambientCount; j++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_AMBIENT, j, &path);
			std::string stdstr(path.C_Str());
			if (ambients.find(stdstr) == ambients.end())
			{
				ambients.emplace(std::make_pair(stdstr, Texture(stdstr, Texture::TextureType::AMBIENT)));
			}
			ambt.push_back(ambients[stdstr].textureID());
		}
		for (int j = 0; j < specularCount; j++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_SPECULAR, j, &path);
			std::string stdstr(path.C_Str());
			if (speculars.find(stdstr) == speculars.end())
			{
				speculars.emplace(std::make_pair(stdstr, Texture(stdstr, Texture::TextureType::SPECULAR)));
			}
			spec.push_back(speculars[stdstr].textureID());
		}
		mesh.setAmbients(ambt);
		mesh.setDiffuses(diff);
		mesh.setSpeuclars(spec);
	}
	void Model::load()
	{
		Assimp::Importer importer = Assimp::Importer();
		const aiScene* scene = importer.ReadFile(model_path.c_str(),aiProcess_GenNormals | aiProcess_Triangulate);
		if (scene == nullptr)
		{
			std::string error = std::string("load") + model_path + "failed";
			PrintInfo(error);
			return;
		}
		processNode(scene, scene->mRootNode);
	}
	Model::~Model()
	{
		PrintFloat(1.f);
		for (auto& diff : diffuses)
		{
			diff.second.free();
		}
		for (auto& spec : speculars)
		{
			spec.second.free();
		}
		for (auto& ambient : ambients)
		{
			ambient.second.free();
		}
	}
};