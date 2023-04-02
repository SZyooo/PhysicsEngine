#version 450 core

layout(triangles) in;
layout(line_strip,max_vertices=2) out;
in vec3 norms[];
uniform mat4 project;
uniform float len;
void main()
{
	vec4 centre = {0,0,0,0};
	for(int i=0;i<gl_in.length();i++)
	{
		centre += gl_in[i].gl_Position;
	}
	centre /= gl_in.length();
	centre.w = 1;
	gl_Position = project * centre;
	EmitVertex();
	gl_Position = project * (centre + len * vec4(norms[0],0));
	EmitVertex();
	EndPrimitive();
}