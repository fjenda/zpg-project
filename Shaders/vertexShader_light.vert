#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec4 vn;

out vec3 normal;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){
    normal = normalize(transpose(inverse(mat3(model))) * vec3(vn));
    position = vec3(model * vp);
    gl_Position = projection * view * model * vp;
}