#version 460 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D g_Geometry;
uniform sampler2D g_Light;

void main(){
	vec4 geometry = texture(g_Geometry, v_TexCoord).rgba;
	vec4 light = texture(g_Light, v_TexCoord).rgba;

	FragColor = geometry * light;
}