#version 450 core
out vec4 color;

in vec4 norm_in_world;
vec3 light = normalize(vec3(1,-1,0));
void main()
{
	vec4 ambient = vec4(0.2,0.2,0.2,0);
	vec4 diffuse = vec4(max(dot(-light,norm_in_world.xyz),0));
	color = ambient + diffuse;
	color.a = 1;
}