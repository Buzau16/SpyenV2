#version 460 core


struct LightData{
	vec2 Color;
	float Radius;
	float Intensity;
};

layout(std140, binding = 3) uniform LC{
	int LightCount;
};

layout(std430, binding = 2) readonly buffer LightDataBuffer{
	LightData ld[];
};

out vec4 FragColor;

void main(){
	FragColor = vec4(1.0);
}