#version 450 core

layout(points) in;
layout(line_strip,max_vertices = 6) out;
uniform vec3 position;
uniform mat4 view;
uniform mat4 proj;
out vec4 color;
void main()
{
	mat4 pv = proj * view;
	vec4 pos = vec4(position,1);
	vec4 origin = pv * vec4(position,1);
	int len = 1;
	//x-axis
	gl_Position = origin;
	color = vec4(1,0,0,1);
	EmitVertex();
	gl_Position = pv * vec4(position+vec3(len,0,0),1);
	color = vec4(1,0,0,1);
	EmitVertex();
	EndPrimitive();

	//y-axis
	gl_Position = origin;
	color = vec4(0,1,0,1);
	EmitVertex();
	gl_Position = pv * vec4(position+vec3(0,len,0),1);
	color = vec4(0,1,0,1);
	EmitVertex();
	EndPrimitive();

	//z-axis
	gl_Position = origin;
	color = vec4(0,0,1,1);
	EmitVertex();
	gl_Position = pv * vec4(position+vec3(0,0,len),1);
	color = vec4(0,0,1,1);
	EmitVertex();
	EndPrimitive();
}