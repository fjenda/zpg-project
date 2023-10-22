#version 330

in vec3 vn_out;
out vec4 frag_color;

void main () {
     frag_color = vec4(vn_out, 1.0);
}