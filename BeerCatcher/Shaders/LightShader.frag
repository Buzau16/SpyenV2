#version 460 core

struct LightData{
	vec3 Color;
    float Radius;
	vec2 Position;
	float Intensity;
    float _padding;
};

layout(std430, binding = 2) readonly buffer LightDataBuffer{
	LightData ld[];
};

layout(std430, binding = 4) readonly buffer OccluderDataBuffer{
	vec2 OccluderVertices[];
};

in flat int v_LightIndex;
in vec2 v_WorldPos;
in vec2 v_TexCoord;
out vec4 FragColor;
uniform int u_LightCount;

void main(){
	vec2 fragPos = gl_FragCoord.xy;
    vec2 lightPos = ld[v_LightIndex].Position;
    float radius = ld[v_LightIndex].Radius;
    
    float dist = length(fragPos - lightPos);

    if (dist > radius) {
        discard;
    }
    
    float attenuation = 1.0 - smoothstep(0.0, radius, dist);
    //attenuation = pow(attenuation, 2.0);
    //float attenuation = clamp(1.0 - dist, 0.0, 1.0);
    vec3 finalColor = ld[v_LightIndex].Color * ld[v_LightIndex].Intensity * attenuation;
    
    FragColor = vec4(finalColor, attenuation);
}