#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;

layout(std140, binding = 1) uniform CameraBuffer{
	mat4 Camera;
};

out vec4 v_Color;
out vec2 v_TexCoord;
out flat int v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = Camera * vec4(a_Position, 0.0, 1.0);
}