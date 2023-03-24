#version 450 core
out vec4 color;

layout(binding = 0)uniform sampler2D tex;


in vec4 norm_in_world;
in vec2 uv;
vec3 light = normalize(vec3(1,-1,0));
void main()
{
	vec4 fragColor = texture(tex,uv);
	if(all(equal(fragColor,vec4(0))))
	{
		fragColor = vec4(1);
	}
	vec4 ambient = vec4(0.2,0.2,0.2,0);
	vec4 diffuse = vec4(max(dot(-light,norm_in_world.xyz),0));
	color = (ambient + diffuse)*fragColor;
	color.a = 1;
}