#version 460

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;

layout(std140, binding = 1) uniform CameraBuffer{
	mat4 Camera;
};

out vec3 v_Color;

void main(){
	v_Color = a_Color;
	gl_Position = Camera * vec4(a_Position, 0.0, 1.0);
}