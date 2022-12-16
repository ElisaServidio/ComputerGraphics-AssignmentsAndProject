	// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.
	glm::mat4 T1, Ry1, Rz1, Rx1, MT1 = glm::mat4(1);	
	T1 = translate(MT1, glm::vec3(1, 0, -1));
	Ry1 = rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0, 1, 0));
   	Rz1 = rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 0, 1));
	Rx1 = rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1, 0, 0));
   	MT1 = T1*Ry1*Rz1*Rx1*inverse(Rz1)*inverse(Ry1)*inverse(T1);

	// Half the size of an object, using as fixed point (5,0,-2)
	glm::mat4 T2, Sp2, MT2 = glm::mat4(1);
	T2 = translate(glm::mat4(1), glm::vec3(5, 0, -2));
	Sp2 = scale(glm::mat4(1), glm::vec3(0.5));
	MT2 = T2*Sp2*inverse(T2);
 
	// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane
	glm::mat4 T3, Rx3, S3, MT3 = glm::mat4(1);
	T3 = translate(glm::mat4(1), glm::vec3(1, 1, 1));
	Rx3 = rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1, 0, 0));
	S3 = scale(glm::mat4(1), glm::vec3(1, -1, 1));
	MT3 = T3*Rx3*S3*inverse(Rx3)*inverse(T3);

	// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.
	glm::mat4 T4, Ry4, Sp4, MT4 = glm::mat4(1);
	T4 = translate(glm::mat4(1), glm::vec3(0, 0, 5));
	Ry4 = rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 1, 0));
	Sp4 = scale(glm::mat4(1), glm::vec3(3));
	MT4 = inverse(T4)*inverse(Ry4)*inverse(Sp4);

