#version 300 es

precision mediump float;

in vec3 fragment_color;
out vec3 color;

void main(void)
{
    color = fragment_color;
}
