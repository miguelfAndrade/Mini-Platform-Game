#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;

uniform mat4 u_Pos;

void main() 
{
    gl_Position = u_Pos * pos;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() 
{
    color = u_Color;
};