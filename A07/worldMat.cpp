/* Create a world matrix using position, Euler angles, and size
It receives as input a glm::vec3 vector called pos, which contains 
the location of the object. The rotation of the object is instead contained in glm::vec3 YPR. In 
particular:
 Euler angles are passed in YPR parameter:
 YPR.x : Yaw
 YPR.y : Pitch
 YPR.z : Roll
Scaling factors along the three main directions are contained in glm::vec3 size */



// Mw = T(px, py, pz) * Ry(phi) * Rx(psi) * Rz(theta) * S(sx, sy, sz)

glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size) {
	glm::mat4 out = glm::mat4(1.0f);
	out =
	glm::translate(glm::mat4(1.0f), glm::vec3(pos)) *
	glm::rotate(glm::mat4(1.0f), glm::radians(YPR.y), glm::vec3(1,0,0)) * 
	glm::rotate(glm::mat4(1.0f), glm::radians(YPR.x), glm::vec3(0,1,0)) *
	glm::rotate(glm::mat4(1.0f), glm::radians(YPR.z), glm::vec3(0,0,1)) *
	glm::scale(glm::mat4(1.0f), glm::vec3(size));
	return out;
}

// Create a world matrix using position, quaternion angles, and size
/*It receives as input a glm::vec3 vector called pos, which contains 
the location of the object. The rotation of the object is instead contained in quaternion
glm::quat rQ. Scaling factors along the three main directions are contained in glm::vec3
size*/
// Mw = T(px, py, pz) * MQ * S(sx, sy, sz)

glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size) {
	glm::mat4 out = glm::mat4(1.0f);
	out =
	glm::translate(glm::mat4(1.0f), glm::vec3(pos)) *
	glm::mat4(rQ) *
	glm::scale(glm::mat4(1.0f), glm::vec3(size));
	return out;
}

