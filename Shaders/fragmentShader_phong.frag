#version 400

in vec3 normal;
in vec3 fragPosition;
out vec4 frag_color;

uniform vec3 cameraPosition;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main(void) {
    vec3 objectColor = vec3(0.263f, 0.78f, 0.8f);
//    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 computedColor = objectColor * lightColor;
    vec3 lightVector = lightPos - fragPosition;
    vec3 ambient = (0.2f * computedColor);

    float diff = max(dot(normalize(lightVector), normalize(normal)), 0.0);

    vec3 view_direction = normalize(cameraPosition - fragPosition);

    vec3 reflect_direction = reflect(-normalize(lightVector), normalize(normal));

    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32.0);
    vec3 specular = 1.0f * spec * computedColor;

    if (dot(normalize(lightVector), normalize(normal)) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    frag_color = vec4(ambient + specular + diff, 1.0f);
}