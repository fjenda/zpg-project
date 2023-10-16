#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

out vec3 vn_out;
out vec3 vp_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
     vn_out = vn;
     vp_out = vp;
     gl_Position = projection * view * model * vec4(vp, 1.0);
}