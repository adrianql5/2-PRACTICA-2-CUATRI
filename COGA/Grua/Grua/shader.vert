#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TextCoord;

void main() {
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = vec3(worldPosition);
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
    TextCoord = aTextCoord;
    gl_Position = projection * view * worldPosition;
}
