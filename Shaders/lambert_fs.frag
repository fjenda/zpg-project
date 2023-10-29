#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

// Lights
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightRadius;

// Material
uniform vec3 r_ambient;
uniform vec3 r_diffuse;
uniform vec3 objectColor;

// lambert shader
void main(void) {
    // light direction
    vec3 lightDir = lightPos - position;

    // attenuation
    float dist = length(lightDir);
    float attenuation = 1 - dist / lightRadius * 2;

    // ambient
    vec3 ambient = r_ambient * lightColor;

    // diffuse
    float diff = max(dot(normalize(lightDir), normalize(normal)), 0.0);
    vec3 diffuse = r_diffuse * diff * lightColor;

    // result
    vec3 result = (ambient + diffuse) * objectColor * lightIntensity * attenuation;
    frag_color = vec4(result, 1.0);
}