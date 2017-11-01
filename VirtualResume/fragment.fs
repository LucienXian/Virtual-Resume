#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D resume1;

void main()
{
	FragColor = texture(resume1, TexCoord);
}