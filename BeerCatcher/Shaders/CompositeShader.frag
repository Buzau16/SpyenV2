#version 460 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D g_Geometry;
uniform sampler2D g_Ambient;

void main(){
	vec4 geometry = texture(g_Geometry, v_TexCoord);
	vec4 ambient = texture(g_Ambient, v_TexCoord);

	FragColor = ambient * geometry;
}