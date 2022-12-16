// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {

	static glm::vec3 pos = glm::vec3(0.0f);
	glm::mat4 out = glm::mat4(1.0f);
	static float yaw = 0.0f; 
	static float roll = 0.0f; 

	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0f;

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>
		(currentTime - startTime).count();
	float deltaT = time - lastTime;
	lastTime = time;

	const float MOVE_SPEED = 1.45f;
	
	glm::mat3 dir = glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f))) *
		        glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f))) *
			glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)));

	if (glfwGetKey(window, GLFW_KEY_A)) {
		yaw = 180.0f;
		roll = 0.0f;
		pos -= MOVE_SPEED * glm::vec3(dir[0]) * deltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		yaw = 0.0f;
		roll = 0.0f;
		pos += MOVE_SPEED * glm::vec3(dir[0]) * deltaT;  
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		yaw = -90.0f;
		roll = 0.0f;
		pos += MOVE_SPEED * glm::vec3(dir[2]) * deltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		yaw = 90.0f;
		roll = 0.0f;
		pos -= MOVE_SPEED * glm::vec3(dir[2]) * deltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_F)) {
		yaw = 0.0f;
        	roll = -90.0f;
        	pos -= MOVE_SPEED * glm::vec3(dir[1]) * deltaT;
    	}
    	if (glfwGetKey(window, GLFW_KEY_R)) {
		yaw = 0.0f;
        	roll = 90.0f;
        	pos += MOVE_SPEED * glm::vec3(dir[1]) * deltaT;
    	}

	out = glm::translate(glm::mat4(1.0), glm::vec3(pos)) * 
	      glm::rotate(glm::mat4(1.0), glm::radians(yaw), glm::vec3(0,1,0)) *
	      glm::rotate(glm::mat4(1.0), glm::radians(roll), glm::vec3(0,0,1));
	
	return out;
}

