#version 450 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 norm;
layout(location = 2) in vec2 uvCoord;
uniform mat4 model,view,project;

out vec4 norm_in_world;
out vec2 uv;
void main()
{
	gl_Position = project * view * model * vec4(pos.xyz,1);
	norm_in_world = transpose(inverse(model)) * vec4(norm.xyz,0);
	uv = uvCoord;
}