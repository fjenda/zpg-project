#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

uniform vec3 cameraPosition;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

// lambert shader
void main(void) {
    // object color
    vec3 objectColor = vec3(0.385, 0.647, 0.812);

    // light direction
    vec3 lightDir = lightPos - position;

    // ambient
    vec3 ambient = 0.1 * lightColor * lightIntensity;

    // diffuse
    float diff = max(dot(normalize(lightDir), normalize(normal)), 0.0) * lightIntensity;
    vec3 diffuse = diff * objectColor;

    // result
    vec3 result = ambient + diffuse;
    frag_color = vec4(result, 1.0);
}