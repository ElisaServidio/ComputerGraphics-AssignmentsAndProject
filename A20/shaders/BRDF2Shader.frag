#version 450#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightColor;
	vec3 eyePos;
} gubo;
layout(set = 0, binding = 3) uniform sampler2D texel;//Implement ambient term plus specular Blinn, directional lightvec3 direct_light_dir(vec3 pos) {	// Directional light direction	return vec3(gubo.lightDir);}vec3 direct_light_color(vec3 pos) {	// Directional light color	return vec3(gubo.lightColor);}vec3 Blinn(vec3 N, vec3 V, vec3 lD, vec3 Cs, float gamma){	//fspec = mS * clamp(nx . hlx)^gamma	//hlx = normalize(lx + wr)	vec3 hlx = normalize(lD + V);	float cl = pow(clamp(dot(N,hlx), 0.0f, 1.0f),gamma);	vec3 BlinnSpec = Cs * cl;	return vec3(BlinnSpec);}void main() {	vec3 Norm = normalize(fragNorm);	vec3 EyeDir = normalize(gubo.eyePos - fragPos);		vec3 lD;	// light direction from the light model	vec3 lC;	// light color and intensity from the light model		lD = direct_light_dir(fragPos);	lC = direct_light_color(fragPos);	float gamma = 200.0f * texture(texel, fragTexCoord).a;		vec3 Ambient = texture(texSampler, fragTexCoord).rgb;		vec3 Specular = texture(texel, fragTexCoord).rgb * Blinn(Norm, EyeDir, lD, lC, gamma);		outColor = vec4(Ambient + Specular, 1.0f);}