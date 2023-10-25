#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

// shader for constant color
void main(void) {
    // object color
    vec3 objectColor = vec3(0.385, 0.647, 0.812);

    // result
    frag_color = vec4(objectColor, 1.0f);
}