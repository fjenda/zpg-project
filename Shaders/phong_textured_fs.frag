#version 400

in vec3 normal;
in vec3 position;
in vec2 texCoord;
out vec4 frag_color;

// Camera
uniform vec3 cameraPosition;

// Light
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

// Attenuation
uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

// Material
uniform vec3 r_ambient;
uniform vec3 r_diffuse;
uniform vec3 r_specular;
uniform float shininess;

// Texture
uniform sampler2D texture0;

void main(void) {
    // light direction
    vec3 lightDir = lightPos - position;

    // attenuation
    float dist = length(lightDir);
    float attenuation = 1.0 / (lightConstant + lightLinear * dist + lightQuadratic * (dist * dist));

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

    // control specular
    if (dot(normal, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    // result
    vec3 result = (ambient + diffuse + specular) * lightIntensity * attenuation;
    frag_color = texture(texture0, texCoord) * vec4(result, 1.0);
}