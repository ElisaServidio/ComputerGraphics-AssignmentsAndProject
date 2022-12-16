/*
The Vertex Shader receives the cartesian local coordinates of each vertex in variable
vec3 inPosition;
and respectively the world, view an projection matrices in components
mat4 worldMat;
mat4 viewMat;
mat4 prjMat;
of the black called ubo . The clipping coordinates of the vertex should be returned in variable
vec4 gl_Position;
*/



#version 450
layout(set = 0, binding = 0) uniform UniformBufferObject {
	mat4 worldMat;
	mat4 viewMat;
	mat4 prjMat;
} ubo;
layout(location = 0) in vec3 inPosition;
layout(location = 0) out float real;
layout(location = 1) out float img;

void main() {
	gl_Position = ubo.prjMat * ubo.viewMat * ubo.worldMat * vec4(inPosition, 1.0);
	real = inPosition.x * 2.5;
	img = inPosition.y * 2.5;
}