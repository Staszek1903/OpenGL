#version 300 es

precision mediump float;

in vec2 uv;
in vec3 normal;

out vec3 FragColor;

uniform vec3 light_vec;
uniform sampler2D texture_samp;

void main()
{
    vec3 color = texture2D(texture_samp, uv).xyz;
    vec3 ambient = color*0.1f;
    float light = -dot(light_vec, normal);
    light = light + 0.3f;
    light = clamp(light,0.0f,1.0f);


    vec3 outcome = (color*light) + ambient;
    FragColor = clamp(outcome, 0.0f, 1.0f);
}
