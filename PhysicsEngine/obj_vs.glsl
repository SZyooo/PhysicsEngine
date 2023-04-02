#version 450 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 norm;
layout(location = 2) in vec2 UVNorm;

out vec2 uv;
out vec3 norm_in_view;
out vec4 pos_in_view;
uniform mat4 view,proj,model;

void main()
{
	uv = UVNorm;
	mat4 mv = view * model;
	pos_in_view = mv * vec4(pos.xyz,1);
	gl_Position = proj * pos_in_view;
	norm_in_view = normalize(transpose(inverse(mat3(mv))) * norm.xyz);
}