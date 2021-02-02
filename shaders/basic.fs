#version 410

in vec3 fragNrm;

void main() {
    gl_FragColor = vec4(fragNrm.zyx, 1.0);
}
