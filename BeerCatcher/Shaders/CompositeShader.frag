#version 460 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D g_Geometry;
uniform sampler2D g_Ambient;
uniform sampler2D g_Light;

void main(){
	vec3 geometry = texture(g_Geometry, v_TexCoord).rgb;
	vec3 ambient = texture(g_Ambient, v_TexCoord).rgb;
	vec3 light = texture(g_Light, v_TexCoord).rgb;

	vec3 total_light = ambient + light;

	FragColor = vec4(geometry * total_light, 1.0);
}