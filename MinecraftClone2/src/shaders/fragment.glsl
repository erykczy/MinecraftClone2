#version 330 core

in vec2 fTexCoord;

uniform sampler2D FrontTexture;

out vec4 FragColor;

void main() {
	FragColor = texture(FrontTexture, fTexCoord);
}
