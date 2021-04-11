#version 410

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNrm;
layout(location = 2) in vec2 inUV;

uniform mat4 MVP;

out vec3 fragNrm;
out vec2 fragUV;

void main()
{
    gl_Position = MVP * vec4(inPos.xyz, 1.0);
    fragNrm = inNrm;
    fragUV = inUV;
    //gl_Position = mat4(1.0) * vec4(inPos.xyz, 1.0);
    //gl_Position = vec4(inPos.xyz, 1.0);
}
