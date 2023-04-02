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
	void Model::drawNorm(const unsigned int program)
	{
		for (auto& mesh : meshs)
		{
			mesh.drawNorm(program);
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
	glm::mat4 fromAiMatrix44(const aiMatrix4x4t<float>& m)
	{
		glm::mat4 res;
		res[0] = { m.a1,m.a2,m.a3,m.a4 };
		res[1] = { m.b1,m.b2,m.b3,m.b4 };
		res[2] = { m.c1,m.c2,m.c3,m.c4 };
		res[3] = { m.d1,m.d2,m.d3,m.d4 };
		return glm::transpose(res);
	}
	void Model::processNode(const aiScene* scene, aiNode* node, const glm::mat4& parentTransform)
	{
		glm::mat4 selfTransform = fromAiMatrix44(node->mTransformation);
		glm::mat4 toChild = parentTransform * selfTransform;
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			processMesh(scene,scene->mMeshes[node->mMeshes[i]], toChild);
		}
		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(scene, node->mChildren[i], toChild);
		}
	}
	Geometry::Vec3D fromaiVector3D(const aiVector3D& v)
	{
		return { v.x,v.y,v.z };
	}
	void Model::processMesh(const aiScene* scene, aiMesh* mesh,const glm::mat4& trans){
		std::vector<YoungEngine::Geometry::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::string name;
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			auto v = mesh->mVertices[i];
			auto n = mesh->mNormals[i];
			name = mesh->mName.C_Str();
			glm::vec4 vertex = { v.x, v.y, v.z, 1 };
			vertex = trans * vertex;
			//Geometry::Vec3D norm = fromaiVector3D(n);
			glm::vec4 norm = { n.x,n.y,n.z,0 };
			norm = glm::transpose(glm::inverse(trans)) * norm;
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
			vert.position = {vertex.x,vertex.y,vertex.z};
			vert.norm = {norm.x,norm.y,norm.z};
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
		std::string model_local_path = model_path.substr(0, model_path.find_last_of('/'));
		for (int j = 0; j < diffuseCount; j++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, j, &path);
			std::string stdstr(path.C_Str());
			if (stdstr[0] != '/')
			{
				stdstr.insert(0, "/");
			}
			stdstr = model_local_path + stdstr;
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
			stdstr = model_local_path + stdstr;
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
			stdstr = model_local_path + stdstr;
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
		const aiScene* scene = importer.ReadFile(model_path.c_str(),aiProcess_GenNormals);
		if (scene == nullptr)
		{
			std::string error = std::string("load ") + model_path + "failed";
			PrintInfo(error);
			return;
		}
		processNode(scene, scene->mRootNode,glm::mat4(1));
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