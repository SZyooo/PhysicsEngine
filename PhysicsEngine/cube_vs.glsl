#version 450 core

layout(location = 0) in vec4 pos;

uniform mat4 model;
uniform mat4 view;

void main()
{
	gl_Position = view * model * vec4(pos.xyz,1);
}