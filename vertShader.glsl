#version 330 core

uniform vec2 center;
uniform vec2 size;

layout (location = 0) in vec3 aPos;
out vec2 c;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	c = vec2(aPos.x * size.x + center.x, aPos.y * size.y + center.y);
}