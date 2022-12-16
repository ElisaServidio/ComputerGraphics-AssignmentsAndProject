#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Create a matrix for Isometric projection with the given aspect ration a
/* Isometric projections are obtained by applying a rotation of ±45° around the y - axis,
   followed by a rotation of ±35.26° around the x - axis, before applying the parallel projection.
   
   M isometric = Port * RX * RY
*/
// w=2, n=-4, f=12 given

glm::mat4 PO1(float a) {
	glm::mat4 out = glm::mat4(1.0);
	
	const float rot_speedY = glm::radians(45.0f);
	glm::mat4 RY = glm::rotate(glm::mat4(1), rot_speedY, glm::vec3(0, 1, 0));

	const float rot_speedX = glm::radians(35.26f);
	glm::mat4 RX = glm::rotate(glm::mat4(1), rot_speedX, glm::vec3(1, 0, 0));

	float w = 2;
	float n = -4;
	float f = 12;

	float l = -w;
	float r = w;
	float b = -w/a;
	float t = w/a;
	
	// This scale matrix flips the y-axis to match the Vulkan conventions.
	glm::mat4 Port = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);

	out = Port * RX * RY;

	return out;
}

// Create a matrix for Dimetric projection (alpha = 45 degree)
// with the given aspect ration a
/* Dimetric projections are obtained by applying a rotation of ±45° around the y-axis, 
   followed by an arbitrary rotation a around the x-axis, before applying the basic parallel projection
*/
glm::mat4 PO2(float a) {

	glm::mat4 out = glm::mat4(1.0);

	const float rot_speedY = glm::radians(45.0f);
	glm::mat4 RY = glm::rotate(glm::mat4(1), rot_speedY, glm::vec3(0, 1, 0));

	const float rot_speedX = glm::radians(45.0f); //arbitrary rotation alpha aound the x-axis
	glm::mat4 RX = glm::rotate(glm::mat4(1), rot_speedX, glm::vec3(1, 0, 0));

	float w = 2;
	float n = -4;
	float f = 12;

	float l = -w;
	float r = w;
	float b = -w / a;
	float t = w / a;


	glm::mat4 Port = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);

	out = Port * RX * RY;

	return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
/* Trimetric projections are obtained by applying an arbitrary rotation b around the y-axis, 
followed by an arbitrary rotation a around the x-axis, before applying the parallel projection
*/
glm::mat4 PO3(float a) {

	glm::mat4 out = glm::mat4(1.0);

	const float rot_speedY = glm::radians(60.0f); //arbitrary rotation b aound the y-axis
	glm::mat4 RY = glm::rotate(glm::mat4(1), rot_speedY, glm::vec3(0, 1, 0));

	const float rot_speedX = glm::radians(45.0f); //arbitrary rotation alpha aound the x-axis
	glm::mat4 RX = glm::rotate(glm::mat4(1), rot_speedX, glm::vec3(1, 0, 0));

	float w = 2;
	float n = -4;
	float f = 12;

	float l = -w;
	float r = w;
	float b = -w / a;
	float t = w / a;


	glm::mat4 Port = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);

	out = Port * RX * RY;

	return out;
}

// Create a matrix for Cabinet projection (alpha = 45) with the given aspect ration a
/* Oblique projections can be obtained by applying a shear along the z-axis before 
   the orthogonal projection. */

glm::mat4 PO4(float a) {

	glm::mat4 out = glm::mat4(1.0);

	const float rot_speedZ = glm::radians(45.0f); //arbitrary rotation b aound the y-axis
	glm::mat4 Shear = glm::mat4(1,0,0,0,  0,1,0,0,  -0.5*cos(rot_speedZ),-0.5*sin(rot_speedZ),1,0,  0,0,0,1);

	float w = 2;
	float n = -4;
	float f = 12;

	float l = -w;
	float r = w;
	float b = -w / a;
	float t = w / a;


	glm::mat4 Port = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);

	out = Port * Shear;

	return out;
}

