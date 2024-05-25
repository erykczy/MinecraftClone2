#version 330 core

in vec2 fTexCoord;
in vec3 fNormal;

uniform sampler2D Texture[6];

out vec4 FragColor;

void main() {
	vec4 frontTex = max(0, -fNormal.z) * texture(Texture[0], fTexCoord);
	vec4 backTex = max(0, fNormal.z) * texture(Texture[1], fTexCoord);
	vec4 upTex = max(0, fNormal.y) * texture(Texture[2], fTexCoord);
	vec4 downTex = max(0, -fNormal.y) * texture(Texture[3], fTexCoord);
	vec4 rightTex = max(0, fNormal.x) * texture(Texture[4], fTexCoord);
	vec4 leftTex = max(0, -fNormal.x) * texture(Texture[5], fTexCoord);

	FragColor = frontTex + backTex + upTex + downTex + rightTex + leftTex;
}
