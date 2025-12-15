#version 460 core
#extension GL_ARB_bindless_texture : require


layout(std430, binding = 0) readonly buffer HandleBuffer{
	sampler2D handles[];
};

in vec4 v_Color;
in vec2 v_TexCoord;
in flat int v_TexIndex;

out vec4 FragColor;

void main()
{
	sampler2D tex = handles[v_TexIndex];
	vec4 texColor = texture(tex, v_TexCoord);
	if(texColor.a < 0.1) discard;

	FragColor = texture(tex, v_TexCoord) * v_Color;
}