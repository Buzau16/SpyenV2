#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;
layout(location = 4) in int a_TrxIndex;

layout(std430, binding = 1) readonly buffer PerObject{
	mat4 Transforms[];
};

out vec3 v_Color;
out vec2 v_TexCoord;
out flat int v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = vec4(a_Position, 0.0f, 1.0) * Transforms[a_TrxIndex];
}