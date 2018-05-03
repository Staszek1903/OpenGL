#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vert_color;
layout (location = 2) in vec3 vert_normal;

uniform mat4 MVP;
uniform mat4 rotate_mat;

out vec3 color;
out vec3 normal;

void main()
{
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = clamp(vert_color,0.0f,1.0f);
    normal = (rotate_mat * vec4(vert_normal,1.0f)).xyz;
}
