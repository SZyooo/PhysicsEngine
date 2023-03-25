#include "Sphere.h"
#include <cmath>

YoungEngine::Geometry::Sphere::Sphere(int detailLv, float r, const glm::mat4& model)
	:Shape(model)
{
	if (detailLv < 5)
	{
		detailLv = 5;
	}
	std::vector<Vertex>& vertices = getVerticesData();

	long double PI = 3.14159265358979323846;
	long double seg1 = 1.f / detailLv;
	long double seg2 = 1.f / (2 * detailLv);
	long double alphaStep = 2 * PI * seg2;
	long double thetaStep = -PI * seg1;
	long double alpha = 0;
	long double theta = PI;
	//theta traverse
	for (int i = 0; i <= detailLv; i++) {
		int m = 2*detailLv;
		double angleTheta = theta + thetaStep * i;
		if (i == 0 || i == detailLv)
		{
			m -= 1;
			if (i == detailLv) {
				angleTheta = 0;
			}
			else
			{
				angleTheta = PI;
			}
		}
		//alpha traverse
		for (int j = 0; j <= m; j++)
		{
			Vec3D v;
			double angleAlpha = alpha + alphaStep * j;
			if (j == 0 && j == m)
			{
				if (j == 0)
				{
					angleAlpha = 0;
				}
				else
				{
					angleAlpha = 2 * PI;
				}
			}
			v.x = r * sin(angleTheta) * cos(angleAlpha);
			v.y = r * sin(angleTheta) * sin(angleAlpha);
			v.z = r * cos(angleTheta);
			Vertex vertex;
			vertex.position = v;
			vertex.norm = v.normalize();
			if (i == 0 || i == detailLv)
			{
				vertex.u = (j + 0.5) * seg2;
			}
			else
			{
				vertex.u = j * seg2;
			}
			vertex.v = i * seg1;
			vertices.push_back(vertex);
		}
	}
	std::vector<unsigned int>& indices = getIndicesData();
	for (int i = 2*detailLv, n = 0; n < 2*detailLv ; n++,i++)
	{
		indices.push_back(i);
		indices.push_back(i - 2 * detailLv);
		indices.push_back(i + 1);
	}
	for (int i = 2; i < detailLv; i++)
	{
		for (int j = (i * (2*detailLv + 1) - 1), n = 0; n < 2*detailLv; j++, n++)
		{
			indices.push_back(j);
			indices.push_back(j - 2 * detailLv - 1);
			indices.push_back(j - 2 * detailLv);
			indices.push_back(j);
			indices.push_back(j - 2 * detailLv);
			indices.push_back(j + 1);
		}
	}
	int num = (detailLv - 1) * (detailLv * 2 + 1) - 1;
	for (int i = num, n = 0; n < 2 * detailLv; i++, n++)
	{
		indices.push_back(i + 2 * detailLv + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
}
