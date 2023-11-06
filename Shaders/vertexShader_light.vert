#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec3 vn;

out vec3 normal;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMatrix;

void main(void){
//    normal = normalize(transpose(inverse(mat3(model))) * vn);
    normal = normalize(mat3(normalMatrix) * vn);
    vec4 pos = model * vp;
    position = pos.xyz / pos.w;
    gl_Position = projection * view * model * vp;
}