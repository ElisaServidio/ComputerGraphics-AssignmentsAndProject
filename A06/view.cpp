// Create a look in direction matrix
// Generally used for first person applications. The user controls the camera position and the view direction.

// Pos    -> Position of the camera
// Angs.x -> direction (alpha)
// Angs.y -> elevation (beta)
// Angs.z -> roll (rho)

// Mv = Mc^-1 = Rz(-rho) * Rx(-beta) * Ry(-alpha) * T(-cx, -cy, -cz)

glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
	
	glm::mat4 out = glm::mat4(1.0);

	out =
		glm::rotate(glm::mat4(1.0), -Angs.z, glm::vec3(0, 0, 1)) * //roll
		glm::rotate(glm::mat4(1.0), -Angs.y, glm::vec3(1, 0, 0)) * //elevation
		glm::rotate(glm::mat4(1.0), -Angs.x, glm::vec3(0, 1, 0)) * //direction
		glm::translate(glm::mat4(1.0), glm::vec3(-Pos.x, -Pos.y, -Pos.z));

	return out;
}

// Create a look at matrix
// Generally employed in third person applications. The camera tracks a point (or an object) aiming at it.

// Pos    -> Position of the camera (c)
// aim    -> Position of the target (a)
// Roll   -> roll (rho)

glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	glm::mat4 out = glm::mat4(1.0);


/* To obtain roll included in the Look - At view matrix:
	Placing a rotation along the z-axis of -rho after transformation of the
	view matrix created
*/
	out = glm::rotate(glm::mat4(1.0), -Roll, glm::vec3(0, 0, 1)) *
	glm::lookAt(glm::vec3(Pos), glm::vec3(aim), glm::vec3(0, 1, 0));

	return out;
}



