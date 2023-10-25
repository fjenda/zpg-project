#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

uniform vec3 cameraPosition;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 r_ambient;
uniform vec3 r_diffuse;
uniform vec3 r_specular;
uniform float shininess;

void main(void) {
    // object color
    vec3 objectColor = vec3(0.385, 0.647, 0.812);

    // light direction
    vec3 lightDir = lightPos - position;

    // ambient
    vec3 ambient = r_ambient * lightColor;

    // diffuse
    float diff = max(dot(normalize(lightDir), normalize(normal)), 0.0);
    vec3 diffuse = r_diffuse * diff * lightColor;

    // specular
    vec3 viewDir = normalize(cameraPosition - position);
    vec3 reflectDir = reflect(-normalize(lightDir), normalize(normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = r_specular * spec * lightColor;

    // result
    vec3 result = (ambient + diffuse + specular) * objectColor;
    frag_color = vec4(result, 1.0);
}