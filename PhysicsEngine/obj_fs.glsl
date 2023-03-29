#version 450 core

out vec4 color;

layout(binding = 0) uniform sampler2D spec;
layout(binding = 1) uniform sampler2D diff;

uniform vec3 light_dir = normalize(vec3(1,-1,0));
uniform mat4 view;
in vec2 uv;
in vec4 norm_in_view;
in vec4 pos_in_view;
void main()
{
	vec4 light_in_view = normalize(view * vec4(light_dir,0));
	float diff_factor = max(dot(norm_in_view.xyz,-light_in_view.xyz),0);
	vec4 reflected_light = reflect(light_in_view,norm_in_view);
	vec4 frag_to_eye = -normalize(pos_in_view);
	float spec_factor = pow(max(dot(frag_to_eye,reflected_light),0),32);
	color = max(diff_factor,0.2) * texture(diff,uv) + spec_factor * texture(spec,uv);
	color.a = 1;
	//color = vec4(1);
}