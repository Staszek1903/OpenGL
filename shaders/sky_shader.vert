#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uv_coord;
layout (location = 2) in vec3 vert_normal;

uniform mat4 MVP;

out vec2 uv;

void main()
{
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = uv_coord;
}
