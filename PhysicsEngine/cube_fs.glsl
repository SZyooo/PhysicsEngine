#version 450 core

out vec4 color;

vec3 light = vec3(1.5,-1,1);
in vec3 norm;
uniform mat4 view;
void main()
{	
	light = normalize((view * vec4(light,0)).xyz);
	color = vec4(1,1,0,1) * max(0,dot(-light,norm))+ vec4(0.2,0.2,0,1);
	color.a = 1;
	//color = vec4(norm,1);
}