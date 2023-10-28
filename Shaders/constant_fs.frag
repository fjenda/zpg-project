#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

uniform vec3 objectColor;

// shader for constant color
void main(void) {
    // result
    frag_color = vec4(objectColor, 1.0f);
}