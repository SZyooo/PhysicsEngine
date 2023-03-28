#include "Model.h"

namespace YoungEngine::Model
{
	inline glm::mat4 YoungEngine::Model::Model::getTransform() const
	{
		return transform.getTransformMatrix();
	}
	void Model::draw(unsigned int vao, unsigned int program)
	{
		int i = 0;
		for (auto& diff : diffuses)
		{
			glBindTextureUnit(i ++, diff.second.textureID());
		}
		for (auto& spec : speculars)
		{
			glBindTextureUnit(i++, spec.second.textureID());
		}
		for (auto& amb : speculars)
		{
			glBindTextureUnit(i++, amb.second.textureID());
		}
		for (auto& mesh : meshs)
		{
			mesh.draw(vao, program);
		}
	}
};