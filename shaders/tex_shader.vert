#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uv_coord;
layout (location = 2) in vec3 vert_normal;

uniform mat4 MVP;
uniform mat4 rotate_mat;

out vec2 uv;
out vec3 normal;

void main()
{
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    normal = (rotate_mat * vec4(vert_normal,1.0f)).xyz;
    uv = uv_coord;
}
