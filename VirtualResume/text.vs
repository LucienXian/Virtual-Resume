#version 330 core
layout (location = 0) in vec3 vertex; 
layout (location = 1) in vec2 textcoord;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
void main()
{
    //gl_Position = projection * vec4(vertex, 1.0);
	gl_Position = projection * view * model *vec4(vertex, 1.0);
	
    TexCoords = textcoord;
}
