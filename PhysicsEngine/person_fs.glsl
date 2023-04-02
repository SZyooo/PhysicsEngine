#version 450 core

out vec4 color;

//layout(binding = 0) uniform sampler2D spec;
layout(binding = 0) uniform sampler2D diff;

uniform vec3 light_dir = normalize(vec3(1,-1,0));
uniform mat4 view;
in vec2 uv;
in vec3 norm_in_view;
in vec4 pos_in_view;
void main()
{
	vec3 light_in_view = normalize(mat3(view) * light_dir);
	float diff_factor = max(dot(norm_in_view.xyz,-light_in_view.xyz),0);
	color = max(diff_factor,0.2) * texture(diff,uv);//+ spec_factor * texture(spec,uv);
	color.a = 1;
	//color = vec4(1);
}