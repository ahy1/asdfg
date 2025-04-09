#type vertex
#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in vec4 a_color;

layout (std140, binding = 0) uniform camera
{
	mat4 u_view_projection;
};
layout (std140, binding = 1) uniform model
{
	mat4 transform;
} u_model;

layout (location = 0) out vec2 v_uv;
layout (location = 1) out vec4 v_color;

void main()
{
	gl_Position = u_view_projection * u_model.transform * vec4(a_position, 1.0);
	v_color = a_color;
	v_uv = a_uv;
}

#type fragment
#version 450 core

layout (location = 0) in vec2 v_uv;
layout (location = 1) in vec4 v_color;

layout (binding = 0) uniform sampler2D u_texture;

layout (location = 0) out vec4 o_color;

void main()
{
	o_color = vec4(texture(u_texture, v_uv).rgb, 1.0);
	if (length(v_uv*2-1)>0.5) {
		o_color = v_color;// / (1 + length(v_uv*2-1)*2-1);
	}
}
