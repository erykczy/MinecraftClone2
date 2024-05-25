#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 fTexCoord;

void main()
{
	fTexCoord = vTexCoord;
	gl_Position = Projection * View * Model * vec4(vPos, 1.0);
}