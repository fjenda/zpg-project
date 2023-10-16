#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec4 vn;

out vec3 normal;
//out vec3 worldPosition;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){
    normal = normalize(transpose(inverse(mat3(model))) * vec3(vn));
    fragPosition = vec3(model * vp);
    gl_Position = projection * view * model * vp;
}