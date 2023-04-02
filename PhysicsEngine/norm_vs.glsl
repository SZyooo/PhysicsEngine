#version 450 core
layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 norm;
layout(location = 2) in vec2 uvCoord;
uniform mat4 model,view,project;

out vec3 norms;
void main()
{
	mat4 mv = view * model;
	gl_Position = mv * vec4(pos.xyz,1);
	norms = transpose(inverse(mat3(mv))) * normalize(norm.xyz);
	norms = normalize(norms);
}