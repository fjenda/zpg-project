#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;

out vec3 normal;
out vec3 position;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    normal = vn;
    position = vp;
    texCoord = vt;
    gl_Position = projection * view * model * vec4(vp, 1.0);
}