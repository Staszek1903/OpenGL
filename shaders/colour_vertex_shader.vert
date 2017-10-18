#version 300 es

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

uniform mat4 MVP;

void main(void)
{
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    fragment_color = vertex_color;
}
