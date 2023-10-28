#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 r_ambient;
uniform vec3 r_diffuse;
uniform vec3 objectColor;

// lambert shader
void main(void) {
    // light direction
    vec3 lightDir = lightPos - position;

    // ambient
    vec3 ambient = r_ambient * lightColor;

    // diffuse
    float diff = max(dot(normalize(lightDir), normalize(normal)), 0.0);
    vec3 diffuse = r_diffuse * diff * lightColor;

    // result
    vec3 result = (ambient + diffuse) * objectColor;
    frag_color = vec4(result, 1.0);
}