#version 450 core

uniform vec3 pos[2];
uniform mat4 view,proj;
void main()
{
    vec4 position = vec4(pos[gl_VertexID].xyz,1);
	gl_Position = proj * view * position;
}