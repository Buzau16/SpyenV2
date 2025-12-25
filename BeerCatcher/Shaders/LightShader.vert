#version 460 core

layout(location = 0) in vec2 a_Position;

layout(std140, binding = 1) uniform CameraBuffer{
	mat4 Camera;
};

void main(){
	gl_Position = Camera * vec4(a_Position, 0.0, 1.0);
}