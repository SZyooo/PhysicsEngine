#version 450 core

uniform vec3 pos[2];
uniform mat4 view,proj;
void main()
{
	gl_Position = proj * view * vec4(pos[gl_VertexID],1);
}