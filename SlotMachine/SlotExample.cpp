// This has been adapted from the Vulkan tutorial

#include "MyProject.hpp"

// The uniform buffer object used in this example
//The two object differ only with respect to the position of the handle and it is inefficient that
//they need to receive two times the proj and the view 
//We have the body in a position with a certain texture and the handle with another position with another texture 
//(so they have a different model matrix and a different texture)
//but they have the same view and projection!
//SO it is better if we create to different sets to match this situation
//SETS WITH A SMOLLER id ARE ASSUMED TO CHANGE LESS OFTEN!!!

/* FIRST VERSION
struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
}; */

//CORRECT VERSION     
//Each set will have a DescriptorSetLayout (DSLglobal, DSLobj)
//SET 0
struct globalUniformBufferObject { //global because it will be the same for every object
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};
//SET 1 binding 0 model matrix
//SET 1 binding 1 texture
struct UniformBufferObject {
	alignas(16) glm::mat4 model;
};


// MAIN ! 
class MyProject : public BaseProject {
	protected:
	// Here you list all the Vulkan objects you need:
	
	// Descriptor Layouts [what will be passed to the shaders]
	DescriptorSetLayout DSLglobal;
	DescriptorSetLayout DSLobj;

	// Pipelines [Shader couples]
	Pipeline P1;

	// Models, textures and Descriptors (values assigned to the uniforms)
	//We add more models and textures
	Model M_SlotBody;
	Texture T_SlotBody;
	DescriptorSet DS_SlotBody; //instance DSLobj

	Model M_SlotHandle;
	Texture T_SlotHandle;
	DescriptorSet DS_SlotHandle; //instance DSLobj

	Model M_SlotWheel;
	Texture T_SlotWheel;
	//We need to have three wheels in different position!
	DescriptorSet DS_SlotWheel1; //instance DSLobj
	DescriptorSet DS_SlotWheel2; //instance DSLobj
	DescriptorSet DS_SlotWheel3; //instance DSLobj

	DescriptorSet DS_global; //instance DSLglobal


	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "My Project";
		
		/*very dark scene
		initialBackgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};*/
		//we change it to make it brighter
		initialBackgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};

		// Descriptor pool sizes
		//The pool MUST count the number of descriptor set!
		uniformBlocksInPool = 6; //for the position of the elements
		texturesInPool = 5; //textures associated to each element
		setsInPool = 6; 
	}
	
	// Here you load and setup all your Vulkan objects
	void localInit() {
		// Descriptor Layouts [what will be passed to the shaders]
		DSLobj.init(this, {
					// this array contains the binding:
					// first  element : the binding number
					// second element : the time of element (buffer or texture)
					// third  element : the pipeline stage where it will be used
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
				  });

		//The third element is ...ALL_GRAPHICS to make it accessible from all shaders
		DSLglobal.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
					});


		// Pipelines [Shader couples]
		// The last array, is a vector of pointer to the layouts of the sets that will
		// be used in this pipeline. The first element will be set 0, and so on..
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", {&DSLglobal, &DSLobj});

		// Models, textures and Descriptors (values assigned to the uniforms)
		//Here we define all the paths for models and textures
		M_SlotBody.init(this, "models/SlotBody.obj");
		T_SlotBody.init(this, "textures/SlotBody.png");
		DS_SlotBody.init(this, &DSLobj, {
		// the second parameter, is a pointer to the Uniform Set Layout of this set
		// the last parameter is an array, with one element per binding of the set.
		// first  elmenet : the binding number
		// second element : UNIFORM or TEXTURE (an enum) depending on the type
		// third  element : only for UNIFORMs, the size of the corresponding C++ object
		// fourth element : only for TEXTUREs, the pointer to the corresponding texture object
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, & T_SlotBody}
				});

		//We add here the other objects
		M_SlotHandle.init(this, "models/SlotHandle.obj");
		T_SlotHandle.init(this, "textures/SlotHandle.png");
		DS_SlotHandle.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, & T_SlotHandle}
				});
		
		//We define three different descriptor sets for SlotWheel 
		//to position the three wheels each one in a different position

		M_SlotWheel.init(this, "models/SlotWheel.obj");
		T_SlotWheel.init(this, "textures/SlotWheel.png");
		DS_SlotWheel1.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, & T_SlotWheel}
				});
		DS_SlotWheel2.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, & T_SlotWheel}
				});
		DS_SlotWheel3.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, & T_SlotWheel}
				});

		
		//Istance for DSLglobal
		DS_global.init(this, &DSLglobal, {
					{0, UNIFORM, sizeof(globalUniformBufferObject), nullptr}
				});
	}

	// Here you destroy all the objects you created!		
	void localCleanup() {
		DS_SlotBody.cleanup();
		T_SlotBody.cleanup();
		M_SlotBody.cleanup();

		DS_SlotHandle.cleanup();
		T_SlotHandle.cleanup();
		M_SlotHandle.cleanup();

		DS_SlotWheel1.cleanup();
		DS_SlotWheel2.cleanup();
		DS_SlotWheel3.cleanup();
		T_SlotWheel.cleanup();
		M_SlotWheel.cleanup();

		DS_global.cleanup();

		P1.cleanup();
		DSLglobal.cleanup();
		DSLobj.cleanup();
		
	}
	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
		
		//For SlotBody and SlotHandle for example the pipeline will be the same because they share the same set of shaders		
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
				P1.graphicsPipeline);

		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 0, 1, &DS_global.descriptorSets[currentImage],
						0, nullptr);
		
		//BUT we will have to use different index buffer and command buffer for SlotBody and SlotHandle	
		VkBuffer vertexBuffers[] = { M_SlotBody.vertexBuffer};
		// property .vertexBuffer of models, contains the VkBuffer handle to its vertex buffer
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		// property .indexBuffer of models, contains the VkBuffer handle to its index buffer
		vkCmdBindIndexBuffer(commandBuffer,  M_SlotBody.indexBuffer, 0,
								VK_INDEX_TYPE_UINT32);

		// property .pipelineLayout of a pipeline contains its layout.
		// property .descriptorSets of a descriptor set contains its elements.
		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 1, 1, &DS_SlotBody.descriptorSets[currentImage],
						0, nullptr);
						
		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>( M_SlotBody.indices.size()), 1, 0, 0, 0);


		//We create the copy here
		VkBuffer vertexBuffers2[] = { M_SlotHandle.vertexBuffer};
		VkDeviceSize offsets2[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers2, offsets2);
		vkCmdBindIndexBuffer(commandBuffer,  M_SlotHandle.indexBuffer, 0,
								VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 1, 1, &DS_SlotHandle.descriptorSets[currentImage],
						0, nullptr);

		//We can already put the draw command
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>( M_SlotHandle.indices.size()), 1, 0, 0, 0);

	

		VkBuffer vertexBuffers3[] = { M_SlotWheel.vertexBuffer};
		VkDeviceSize offsets3[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers3, offsets3);
		vkCmdBindIndexBuffer(commandBuffer,  M_SlotWheel.indexBuffer, 0,
								VK_INDEX_TYPE_UINT32);

		//We repeat the following command three times each time binding a different descriptor set (1 or 2 or 3)
		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 1, 1, &DS_SlotWheel1.descriptorSets[currentImage],
						0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>( M_SlotWheel.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 1, 1, &DS_SlotWheel2.descriptorSets[currentImage],
						0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>( M_SlotWheel.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 1, 1, &DS_SlotWheel3.descriptorSets[currentImage],
						0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>( M_SlotWheel.indices.size()), 1, 0, 0, 0);
	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
					(currentTime - startTime).count();
		static float lastTime = 0.0f;
		float deltaT = time - lastTime;
		lastTime = time;

		//We have to make the wheels rotate pressing space!
		static int state = 0; 	//0 - everything is still	
					//3 - three wheels are turning 
					//2 - two wheels are turning 	
					//1 - one wheel is turning 

		
		static float debounce = time;
		static float ang1 = 0.0f;
		static float ang2 = 0.0f;
		static float ang3 = 0.0f;

		if(glfwGetKey(window, GLFW_KEY_SPACE)) {
			if(time - debounce > 0.33) {
				debounce = time;
				if(state == 0) {
					state = 3;
				} else {
					state--;	
				}
			}	
		}

		if (state == 3) {
			ang3 += deltaT;
		}

		if (state >= 2) {
			ang2 += deltaT;
		}

		if (state >= 1) {
			ang1 += deltaT;
		}

		globalUniformBufferObject gubo{};			
		UniformBufferObject ubo{};

		void* data;

	
		/*the last vector glm::vec3(0.0f, 0.0f, 1.0f) makes the object rotate on the floor
		gubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
							   glm::vec3(0.0f, 0.0f, 0.0f),
							   glm::vec3(0.0f, 0.0f, 1.0f)); */

		//we replace it with glm::vec3(0.0f, 1.0f, 0.0f) to put the object in vertical position
		gubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
							   glm::vec3(0.0f, 0.0f, 0.0f),
							   glm::vec3(0.0f, 1.0f, 0.0f)); 


		gubo.proj = glm::perspective(glm::radians(45.0f),
						swapChainExtent.width / (float) swapChainExtent.height,
						0.1f, 10.0f);
		gubo.proj[1][1] *= -1;

		vkMapMemory(device, DS_global.uniformBuffersMemory[0][currentImage], 0,
							sizeof(gubo), 0, &data);
		memcpy(data, &gubo, sizeof(gubo));
		vkUnmapMemory(device, DS_global.uniformBuffersMemory[0][currentImage]);
		

		// Here is where you actually update your uniforms: FOR THE SLOTBODY
		/* to make the object rotate:
		ubo.model = glm::rotate(glm::mat4(1.0f),
								time * glm::radians(90.0f),
								glm::vec3(0.0f, 0.0f, 1.0f)); */

		//still object
		ubo.model = glm::mat4(1.0f);
		vkMapMemory(device, DS_SlotBody.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_SlotBody.uniformBuffersMemory[0][currentImage]);

		// Here is where you actually update your uniforms: FOR THE SLOTHANDLE
		//steady object BUT we have to translate it to put it in the right position over the SlotHandle
		//it depends on the center of the SlotHandle object modeled in blender
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.5f, -0.15f));
		vkMapMemory(device, DS_SlotHandle.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_SlotHandle.uniformBuffersMemory[0][currentImage]);

		// Here is where you actually update your uniforms: FOR THE SLOTWHEEL
		//We make the wheel turning (see ubo.model)!
		// DS_SlotWheel1
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f, 0.93f, -0.15f))*
			    glm::rotate(glm::mat4(1.0f), ang1 * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		vkMapMemory(device, DS_SlotWheel1.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_SlotWheel1.uniformBuffersMemory[0][currentImage]);
		// DS_SlotWheel2
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.93f, -0.15f))*
			    glm::rotate(glm::mat4(1.0f), ang2 * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		vkMapMemory(device, DS_SlotWheel2.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_SlotWheel2.uniformBuffersMemory[0][currentImage]);
		// DS_SlotWheel3
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, 0.93f, -0.15f))*
			    glm::rotate(glm::mat4(1.0f), ang3 * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		vkMapMemory(device, DS_SlotWheel3.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_SlotWheel3.uniformBuffersMemory[0][currentImage]);
	}	
};

// This is the main: probably you do not need to touch this!
int main() {
    MyProject app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}