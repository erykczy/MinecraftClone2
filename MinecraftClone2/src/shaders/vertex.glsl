#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 fTexCoord;
out vec3 fNormal;

void main()
{
	fTexCoord = vTexCoord;
	fNormal = vNormal;
	gl_Position = Projection * View * Model * vec4(vPos, 1.0);
}