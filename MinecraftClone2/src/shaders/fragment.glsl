#version 330 core

in vec2 fTexCoord;
in vec3 fNormal;
in float fAmbientOcclusion;

uniform sampler2D Texture[6];

out vec4 FragColor;

void main() {
	vec4 frontTex = max(0, -fNormal.z) * texture(Texture[0], fTexCoord);
	vec4 backTex = max(0, fNormal.z) * texture(Texture[1], fTexCoord);
	vec4 upTex = max(0, fNormal.y) * texture(Texture[2], fTexCoord);
	vec4 downTex = max(0, -fNormal.y) * texture(Texture[3], fTexCoord);
	vec4 rightTex = max(0, fNormal.x) * texture(Texture[4], fTexCoord);
	vec4 leftTex = max(0, -fNormal.x) * texture(Texture[5], fTexCoord);
	vec4 tex = frontTex + backTex + upTex + downTex + rightTex + leftTex;
	
	float diffuseUp = dot(fNormal, normalize(vec3(0.0, 1.0, 0.0)));
	float diffuseNorth = dot(fNormal, normalize(vec3(0.0, 0.0, -1.0)));
	float diffuseSouth = dot(fNormal, normalize(vec3(0.0, 0.0, 1.0)));
	float diffuse = clamp(max(diffuseSouth, max(diffuseUp, diffuseNorth)), 0.5, 0.8);

	vec4 ambientOcclusion = 1 - 0.5 * vec4(fAmbientOcclusion, fAmbientOcclusion, fAmbientOcclusion, 0.0);

	FragColor = tex * ambientOcclusion * diffuse;
}
