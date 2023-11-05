#version 400

in vec3 normal;
in vec3 position;
out vec4 frag_color;

// Camera
uniform vec3 cameraPosition;

// Lights
#define MAX_LIGHTS 16
uniform int lightCount;

struct Light {
    int type; // for light type

    vec3 position;
    vec3 color;
    vec3 direction;

    // for spot-light
    float innerCutoff;
    float outerCutoff;

    float intensity;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];

// Material
uniform vec3 r_ambient;
uniform vec3 r_diffuse;
uniform vec3 r_specular;
uniform float shininess;
uniform vec3 objectColor;

// Point-light
vec3 pointLight(Light light_, vec3 norm, vec3 fragPosition, vec3 viewDir) {
    // light direction
    vec3 lightDir = normalize(light_.position - fragPosition);

    // attenuation
    float dist = length(light_.position - fragPosition);
    float attenuation = 1.0 / (light_.constant + light_.linear * dist + light_.quadratic * (dist * dist));

    // ambient
    vec3 ambient = r_ambient * light_.color;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = r_diffuse * diff * light_.color;

    // specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = r_specular * spec * light_.color;

    // control specular
    if (dot(normal, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    // result
    return (ambient + diffuse + specular) * attenuation * light_.intensity;
}

// Directional-light
vec3 directionalLight(Light light_, vec3 norm, vec3 fragPosition, vec3 viewDir) {
    // light direction
    vec3 lightDir = normalize(-light_.direction);

    // ambient
    vec3 ambient = r_ambient * light_.color;

    // diffuse
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = r_diffuse * diff * light_.color;

    // specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = r_specular * spec * light_.color;

    // control specular
    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    // result
    return (ambient + diffuse + specular) * light_.intensity;
}

// Spot-light
//vec3 spotLight(Light light_, vec3 norm, vec3 fragPosition, vec3 viewDir) {
//    // light direction
//    vec3 lightDir = normalize(light_.position - fragPosition);
//
//    // ambient
//    vec3 ambient = r_ambient * light_.color;
//
//    // attenuation
//    float dist = length(light_.position - fragPosition);
//    float attenuation = 1.0 / (light_.constant + light_.linear * dist + light_.quadratic * (dist * dist));
//
//    float theta = dot(lightDir, normalize(-light_.direction));
//    if (theta > light_.innerCutoff) {
//        float intensity = (1.0 - (1.0 - theta) / (1.0 - light_.innerCutoff));
//
//        // diffuse
//        float diff = max(dot(norm, lightDir), 0.0);
//        vec3 diffuse = r_diffuse * diff * light_.color * intensity;
//
//        // specular
//        vec3 reflectDir = reflect(-lightDir, norm);
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
//        vec3 specular = r_specular * spec * light_.color * intensity;
//
//        if (dot(norm, lightDir) < 0.0){
//            specular = vec3(0.0f, 0.0f, 0.0f);
//        }
//        return ambient + diffuse + specular;
//    } else {
//        return vec3(0.0f, 0.0f, 0.0f);
//    }
//}


vec3 spotLight(Light light_, vec3 norm, vec3 fragPosition, vec3 viewDir) {
    // light direction
    vec3 lightDir = normalize(light_.position - fragPosition);

    // attenuation
    float dist = length(light_.position - fragPosition);
    float attenuation = 1.0 / (light_.constant + light_.linear * dist + light_.quadratic * (dist * dist));

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light_.direction));
    float epsilon = light_.innerCutoff - light_.outerCutoff;
    float intensity = clamp((theta - light_.outerCutoff) / epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient = r_ambient * light_.color * intensity * attenuation * light_.intensity;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = r_diffuse * diff * light_.color * intensity * attenuation * light_.intensity;

    // specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = r_specular * spec * light_.color * intensity * attenuation * light_.intensity;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    return ambient + diffuse + specular;
}

void main(void) {
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(cameraPosition - position);


    vec3 result = vec3(0.f);
    for (int i = 0; i < lightCount; i++) {
        lights[i].type == 0 ? (result += pointLight(lights[i], norm, position, viewDir)) : result;
        lights[i].type == 1 ? (result += directionalLight(lights[i], norm, position, viewDir)) : result;
        lights[i].type == 2 ? (result += spotLight(lights[i], norm, position, viewDir)) : result;
    }

    result *= objectColor;
    frag_color = vec4(result, 1.0);
}