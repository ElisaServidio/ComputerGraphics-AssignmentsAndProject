#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;


layout(set = 0, binding = 2) uniform GlobalUniformBufferObject {
} gubo;

void main() {
	
}