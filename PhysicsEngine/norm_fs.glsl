#version 450 core

out vec4 color;
uniform vec3 normColor;
void main()
{
	color = vec4(normColor,1);
}