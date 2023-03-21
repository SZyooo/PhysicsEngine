#version 450 core

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices = 3) out;

out vec3 norm;
uniform mat4 project;
void main()
{
	vec4 p1 = gl_in[1].gl_Position - gl_in[0].gl_Position;
	vec4 p2 = gl_in[2].gl_Position - gl_in[0].gl_Position;
	norm = normalize(cross(p1.xyz,p2.xyz));
	gl_Position = project * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = project * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = project * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}