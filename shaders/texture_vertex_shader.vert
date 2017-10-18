#version 300 es

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

void main(void)
{
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    // Position of the vertex, in worldspace : M * position
    vec4 pos_world = (M * vec4(vertexPosition_modelspace,1));
    Position_worldspace = pos_world.xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
    vec4 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1));
    vec3 vertpos_camera = vertexPosition_cameraspace.xyz;
    EyeDirection_cameraspace = vec3(0,0,0) - vertpos_camera;

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
    vec4 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1));
    vec3 lightpos_camera = LightPosition_cameraspace.xyz;
    LightDirection_cameraspace = lightpos_camera + EyeDirection_cameraspace;

    // Normal of the the vertex, in camera space
    vec4 normal_camera =  ( V * M * vec4(vertexNormal_modelspace,0));
    Normal_cameraspace = normal_camera.xyz;
    // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
    UV = vertexUV;
}
