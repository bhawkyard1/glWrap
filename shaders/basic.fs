#version 410

in vec3 fragNrm;
in vec2 fragUV;

void main() {
    gl_FragColor = vec4(fragNrm.xyz, 1.0);
}
