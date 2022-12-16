// Create a matrix for Perspective projection with the given aspect ratio a,
// and a FovY = 90o
//fov, a, n, f are respectively the vertical field of 
//view, the aspect ratio, the near and the far plane distances
glm::mat4 PO1(float a) {
  	float n = 0.1f;	
	float f = 9.9f;
	glm::mat4 out = glm::perspective(glm::radians(90.0f), a, n, f);
	/* Since the Vulkanand OpenGL matrices for Fov / Aspect ratio projection differ only for the sign of the element in the second row / second column,
 	in this special case it could be more convenient to just change the sign of this element instead of applying a mirroring transform 
 	*/
	out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspective projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
  	float n = 0.1f;	
	float f = 9.9f;
	glm::mat4 out = glm::perspective(glm::radians(120.0f), a, n, f);
	out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspective projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
  	float n = 0.1f;	
	float f = 9.9f;
	glm::mat4 out = glm::perspective(glm::radians(30.0f), a, n, f);
	out[1][1] *= -1;
	return out;
}

// Create a matrix for Perspective projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
  	float n = 0.1f;	
	float f = 9.9f;
	float r = 0.0f;
  	float l = -a*n*tan(glm::radians(90.0f)/2);	
	float t = n*tan(glm::radians(90.0f)/2);
	float b = -n*tan(glm::radians(90.0f)/2);
	glm::mat4 out = glm::scale(glm::mat4(1.0), glm::vec3(1,-1,1)) * //This added matrix product flips the y-axis to match the Vulkan conventions
	glm::frustum(l, r, b, t, n, f);
	
        /*GLM provides the frustum() function to compute the 
	perspective projection matrix specifying the boundaries:
	Where l, r, b, t, n, f are the positions in world 
	coordinates respectively of the left, right, bottom, top, near and 
	far boundaries of the visible region*/

	return out;
}

