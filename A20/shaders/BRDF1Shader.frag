#version 450#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform GlobalUniformBufferObject {	vec3 lightDir;	vec3 lightPos;	vec3 lightColor;	vec4 lightParams;	vec3 eyePos;
} gubo;
layout(set = 0, binding = 3) uniform sampler2D texel;//Implement Lambert with specular Phong, spot lightvec3 spot_light_dir(vec3 pos) {	// Spot light direction	return normalize(vec3(gubo.lightPos)- pos);}vec3 spot_light_color(vec3 pos) {	// Spot light color		vec3 norm = normalize(vec3(gubo.lightPos)- pos);	vec3 d = gubo.lightDir;	float cosOut = gubo.lightParams.y;	float cosIn = gubo.lightParams.x;	float g = gubo.lightParams.w;	float beta = gubo.lightParams.z;	vec3 l = gubo.lightColor;	vec3 distance = vec3(gubo.lightPos) - pos;	float modD = length(distance);		float p = pow((g/modD), beta);		float cl = clamp((dot(norm,d) - cosOut)/(cosIn - cosOut), 0.0f, 1.0f);	return vec3(l * p * cl);		}vec3 Lambert(vec3 N, vec3 L, vec3 Cd){		// fdiff = mD * max (lx, nx, 0)		float max = max(dot(L, N), 0.0f);	vec3 LambertDiffuse = Cd * max;	return LambertDiffuse;	}	vec3 Phong(vec3 N, vec3 V, vec3 L, vec3 Cd, float gamma){		//fspec = mS * clamp(wr . r)^gamma	//r = -reflect(xl, nx)		vec3 r = -reflect(L, N);	float cl = pow(clamp(dot(V,r), 0.0f, 1.0f),gamma);	vec3 specPhong = vec3(Cd * cl);	return specPhong;}
void main() {
		vec3 Norm = normalize(fragNorm);	vec3 EyeDir = normalize(gubo.eyePos - fragPos);	float gamma = 200.0f * texture(texel, fragTexCoord).a;	vec3 lD;	// light direction from the light model	vec3 lC;	// light color and intensity from the light model		lD = spot_light_dir(fragPos);	lC = spot_light_color(fragPos);	vec3 Diffuse = texture(texSampler, fragTexCoord).rgb * Lambert(Norm, lD, lC);		vec3 Specular = texture(texel, fragTexCoord).rgb * Phong(Norm, EyeDir, lD, lC, gamma);			outColor = vec4(Diffuse+Specular, 1.0f);
}