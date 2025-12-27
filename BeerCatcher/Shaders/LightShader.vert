#version 460 core

	layout(location = 0) in vec2 a_Position;
	layout(location = 1) in int a_LightIndex;

	layout(std140, binding = 1) uniform CameraBuffer{
		mat4 Camera;
	};

	out flat int v_LightIndex;
	out vec2 v_WorldPos;
	out vec2 v_TexCoord;

	void main(){
		v_LightIndex = a_LightIndex;
		v_WorldPos = a_Position;
		v_TexCoord = a_Position * 0.5 + 0.5;
		gl_Position = Camera * vec4(a_Position, 0.0, 1.0);
	}