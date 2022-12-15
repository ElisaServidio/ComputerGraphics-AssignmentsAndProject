
#include "MyProject.hpp"

//The objects have the same view and projection!
//SO it is better if we create two different sets to match this situation
//SETS WITH A SMALLER id ARE ASSUMED TO CHANGE LESS OFTEN!!!

//CORRECT VERSION     
//Each set will have a DescriptorSetLayout (DSLglobal, DSLobj)
//The DSL describes which bindings are in the DescriptorSet for every shader stage. 
// The descriptor layout specifies the types of resources that are going to be accessed by the pipeline
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
	// Here there are all the Vulkan objects we need:

	// Descriptor Layouts [what will be passed to the shaders]
	DescriptorSetLayout DSLglobal;
	DescriptorSetLayout DSLobj;

	// Pipelines [Shader couples]
	Pipeline P1;

	// Models, textures and Descriptors (values assigned to the uniforms)

	//We add more models and textures 

	//Title
	Model M_Title;
	Texture T_Title;
	DescriptorSet DS_Title; //instance DSLobj

	//Table
	Model M_Table;
	Texture T_Table;
	DescriptorSet DS_Table; //instance DSLobj

	//Table with tangram1
	Model M_Tangram1;
	Texture T_Tangram1;
	DescriptorSet DS_Tangram1; //instance DSLobj

	//Table with tangram2
	Model M_Tangram2;
	Texture T_Tangram2;
	DescriptorSet DS_Tangram2; //instance DSLobj

	//Piece1
	Model M_Piece1;
	Texture T_Piece1;
	DescriptorSet DS_Piece1; //instance DSLobj

	//Piece1
	Model M_SelectedPiece1;
	Texture T_SelectedPiece1;
	DescriptorSet DS_SelectedPiece1; //instance DSLobj

	//Piece2
	Model M_Piece2;
	Texture T_Piece2;
	DescriptorSet DS_Piece2; //instance DSLobj

	//Piece2
	Model M_SelectedPiece2;
	Texture T_SelectedPiece2;
	DescriptorSet DS_SelectedPiece2; //instance DSLobj

	//Piece3
	Model M_Piece3;
	Texture T_Piece3;
	DescriptorSet DS_Piece3; //instance DSLobj

	//Piece3
	Model M_SelectedPiece3;
	Texture T_SelectedPiece3;
	DescriptorSet DS_SelectedPiece3; //instance DSLobj

	//Piece4
	Model M_Piece4;
	Texture T_Piece4;
	DescriptorSet DS_Piece4; //instance DSLobj

	//Piece4
	Model M_SelectedPiece4;
	Texture T_SelectedPiece4;
	DescriptorSet DS_SelectedPiece4; //instance DSLobj

	//Piece5
	Model M_Piece5;
	Texture T_Piece5;
	DescriptorSet DS_Piece5; //instance DSLobj

	//Piece5
	Model M_SelectedPiece5;
	Texture T_SelectedPiece5;
	DescriptorSet DS_SelectedPiece5; //instance DSLobj

	//Piece6
	Model M_Piece6;
	Texture T_Piece6;
	DescriptorSet DS_Piece6; //instance DSLobj

	//Piece6
	Model M_SelectedPiece6;
	Texture T_SelectedPiece6;
	DescriptorSet DS_SelectedPiece6; //instance DSLobj

	//Piece7
	Model M_Piece7;
	Texture T_Piece7;
	DescriptorSet DS_Piece7; //instance DSLobj

	//Piece7
	Model M_SelectedPiece7;
	Texture T_SelectedPiece7;
	DescriptorSet DS_SelectedPiece7; //instance DSLobj

	//Tray
	Model M_Tray;
	Texture T_Tray;
	DescriptorSet DS_Tray; //instance DSLobj

	//PlayButton
	Model M_PlayButton;
	Texture T_PlayButton;
	DescriptorSet DS_PlayButton; //instance DSLobj

	//Instructions
	Model M_Instructions;
	Texture T_Instructions;
	DescriptorSet DS_Instructions; //instance DSLobj

	//Wall
	Model M_Wall;
	Texture T_Wall;
	DescriptorSet DS_Wall; //instance DSLobj

	//Walldx
	Model M_Walldx;
	Texture T_Walldx;
	DescriptorSet DS_Walldx; //instance DSLobj

	//Wallsx
	Model M_Wallsx;
	Texture T_Wallsx;
	DescriptorSet DS_Wallsx; //instance DSLobj

	DescriptorSet DS_global; //instance DSLglobal


	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 3840;
		windowHeight = 2160;
		windowTitle = "Tangram";

		initialBackgroundColor = { 1.0f, 1.0f, 1.0f };

		// Descriptor pool sizes
		//The pool MUST count the number of descriptor set!
		uniformBlocksInPool = 25; //for the position of the elements
		texturesInPool = 24; //textures associated to each element
		setsInPool = 25;
	}

	// Here you load and setup all your Vulkan objects
	void localInit() {
		// Descriptor Layouts [what will be passed to the shaders]
		DSLobj.init(this, {
			// this array contains the binding:
			// first  element : the binding number
			// second element : the type of element (buffer or texture)
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
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &DSLglobal, &DSLobj });

		// Models, textures and Descriptors (values assigned to the uniforms)
		//Here we define all the paths for models and textures
		//Title
		M_Title.init(this, "models/Title.obj");
		T_Title.init(this, "textures/Title.jpg");
		DS_Title.init(this, &DSLobj, {
			// the second parameter, is a pointer to the Uniform Set Layout of this set
			// the last parameter is an array, with one element per binding of the set.
			// first  elmenet : the binding number
			// second element : UNIFORM or TEXTURE (an enum) depending on the type
			// third  element : only for UNIFORMs, the size of the corresponding C++ object
			// fourth element : only for TEXTUREs, the pointer to the corresponding texture object
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &T_Title}
			});

		//We add here the other objects
		//Table
		M_Table.init(this, "models/Table.obj");
		T_Table.init(this, "textures/Table.jpg");

		DS_Table.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Table}
			});

		//Table with tangram1 (+ instructions)
		M_Tangram1.init(this, "models/Table.obj");
		T_Tangram1.init(this, "textures/Tangram1.png");

		DS_Tangram1.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Tangram1}
			});

		//Table with tangram2 (+ instructions)
		M_Tangram2.init(this, "models/Table.obj");
		T_Tangram2.init(this, "textures/Tangram2.png");

		DS_Tangram2.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Tangram2}
			});

		//Piece1
		M_Piece1.init(this, "models/Piece1.obj");
		T_Piece1.init(this, "textures/Piece1.jpg");
		DS_Piece1.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece1}
			});

		//SelectedPiece1
		M_SelectedPiece1.init(this, "models/Piece1.obj");
		T_SelectedPiece1.init(this, "textures/SelectedPiece1.jpg");
		DS_SelectedPiece1.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece1}
			});

		//Piece2
		M_Piece2.init(this, "models/Piece2.obj");
		T_Piece2.init(this, "textures/Piece2.jpg");
		DS_Piece2.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece2}
			});

		//SelectedPiece2
		M_SelectedPiece2.init(this, "models/Piece2.obj");
		T_SelectedPiece2.init(this, "textures/SelectedPiece2.jpg");
		DS_SelectedPiece2.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece2}
			});

		//Piece3
		M_Piece3.init(this, "models/Piece3.obj");
		T_Piece3.init(this, "textures/Piece3.jpg");
		DS_Piece3.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece3}
			});

		//SelectedPiece3
		M_SelectedPiece3.init(this, "models/Piece3.obj");
		T_SelectedPiece3.init(this, "textures/SelectedPiece3.jpg");
		DS_SelectedPiece3.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece3}
			});

		//Piece4
		M_Piece4.init(this, "models/Piece4.obj");
		T_Piece4.init(this, "textures/Piece4.jpg");
		DS_Piece4.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece4}
			});

		//SelectedPiece4
		M_SelectedPiece4.init(this, "models/Piece4.obj");
		T_SelectedPiece4.init(this, "textures/SelectedPiece4.jpg");
		DS_SelectedPiece4.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece4}
			});

		//Piece5
		M_Piece5.init(this, "models/Piece5.obj");
		T_Piece5.init(this, "textures/Piece5.jpg");
		DS_Piece5.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece5}
			});

		//SelectedPiece5
		M_SelectedPiece5.init(this, "models/Piece5.obj");
		T_SelectedPiece5.init(this, "textures/SelectedPiece5.jpg");
		DS_SelectedPiece5.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece5}
			});

		//Piece6
		M_Piece6.init(this, "models/Piece6.obj");
		T_Piece6.init(this, "textures/Piece6.jpg");
		DS_Piece6.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece6}
			});

		//SelectedPiece6
		M_SelectedPiece6.init(this, "models/Piece6.obj");
		T_SelectedPiece6.init(this, "textures/SelectedPiece6.jpg");
		DS_SelectedPiece6.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece6}
			});


		//Piece7
		M_Piece7.init(this, "models/Piece7.obj");
		T_Piece7.init(this, "textures/Piece7.jpg");
		DS_Piece7.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Piece7}
			});

		//SelectedPiece2
		M_SelectedPiece7.init(this, "models/Piece7.obj");
		T_SelectedPiece7.init(this, "textures/SelectedPiece7.jpg");
		DS_SelectedPiece7.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_SelectedPiece7}
			});

		//Tray
		M_Tray.init(this, "models/Tray.obj");
		T_Tray.init(this, "textures/Tray.png");
		DS_Tray.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Tray}
			});

		//PlayButton
		M_PlayButton.init(this, "models/PlayButton.obj");
		T_PlayButton.init(this, "textures/PlayButton.jpg");
		DS_PlayButton.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_PlayButton}
			});

		//Table with only Instructions
		M_Instructions.init(this, "models/Table.obj");
		T_Instructions.init(this, "textures/Instructions.jpg");
		DS_Instructions.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Instructions}
			});

		//Wall
		M_Wall.init(this, "models/Table.obj");
		T_Wall.init(this, "textures/Table.jpg");
		DS_Wall.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Wall}
			});

		//Walldx
		M_Walldx.init(this, "models/Table.obj");
		T_Walldx.init(this, "textures/Table.jpg");
		DS_Walldx.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Walldx}
			});

		//Wallsx
		M_Wallsx.init(this, "models/Table.obj");
		T_Wallsx.init(this, "textures/Table.jpg");
		DS_Wallsx.init(this, &DSLobj, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &T_Wallsx}
			});

		//Istance for DSLglobal
		DS_global.init(this, &DSLglobal, {
					{0, UNIFORM, sizeof(globalUniformBufferObject), nullptr}
			});
	}

	// Here you destroy all the objects you created!		
	void localCleanup() {

		DS_Title.cleanup();
		T_Title.cleanup();
		M_Title.cleanup();

		DS_Table.cleanup();
		T_Table.cleanup();
		M_Table.cleanup();

		DS_Tangram1.cleanup();
		T_Tangram1.cleanup();
		M_Tangram1.cleanup();

		DS_Tangram2.cleanup();
		T_Tangram2.cleanup();
		M_Tangram2.cleanup();

		DS_Piece1.cleanup();
		T_Piece1.cleanup();
		M_Piece1.cleanup();

		DS_SelectedPiece1.cleanup();
		T_SelectedPiece1.cleanup();
		M_SelectedPiece1.cleanup();

		DS_Piece2.cleanup();
		T_Piece2.cleanup();
		M_Piece2.cleanup();

		DS_SelectedPiece2.cleanup();
		T_SelectedPiece2.cleanup();
		M_SelectedPiece2.cleanup();

		DS_Piece3.cleanup();
		T_Piece3.cleanup();
		M_Piece3.cleanup();

		DS_SelectedPiece3.cleanup();
		T_SelectedPiece3.cleanup();
		M_SelectedPiece3.cleanup();

		DS_Piece4.cleanup();
		T_Piece4.cleanup();
		M_Piece4.cleanup();

		DS_SelectedPiece4.cleanup();
		T_SelectedPiece4.cleanup();
		M_SelectedPiece4.cleanup();

		DS_Piece5.cleanup();
		T_Piece5.cleanup();
		M_Piece5.cleanup();

		DS_SelectedPiece5.cleanup();
		T_SelectedPiece5.cleanup();
		M_SelectedPiece5.cleanup();

		DS_Piece6.cleanup();
		T_Piece6.cleanup();
		M_Piece6.cleanup();

		DS_SelectedPiece6.cleanup();
		T_SelectedPiece6.cleanup();
		M_SelectedPiece6.cleanup();

		DS_Piece7.cleanup();
		T_Piece7.cleanup();
		M_Piece7.cleanup();

		DS_SelectedPiece7.cleanup();
		T_SelectedPiece7.cleanup();
		M_SelectedPiece7.cleanup();

		DS_Tray.cleanup();
		T_Tray.cleanup();
		M_Tray.cleanup();

		DS_PlayButton.cleanup();
		T_PlayButton.cleanup();
		M_PlayButton.cleanup();

		DS_Instructions.cleanup();
		T_Instructions.cleanup();
		M_Instructions.cleanup();

		DS_Wall.cleanup();
		T_Wall.cleanup();
		M_Wall.cleanup();

		DS_Walldx.cleanup();
		T_Walldx.cleanup();
		M_Walldx.cleanup();

		DS_Wallsx.cleanup();
		T_Wallsx.cleanup();
		M_Wallsx.cleanup();

		DS_global.cleanup();

		P1.cleanup();
		DSLglobal.cleanup();
		DSLobj.cleanup();

	}

	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {

		//For all objects the pipeline will be the same because they share the same set of shaders		
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.graphicsPipeline);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 0, 1, &DS_global.descriptorSets[currentImage],
			0, nullptr);

		//TITLE

		//BUT we will have to use different index buffer and command buffer for the objects
		VkBuffer vertexBuffers[] = { M_Title.vertexBuffer };
		// property .vertexBuffer of models, contains the VkBuffer handle to its vertex buffer
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		// property .indexBuffer of models, contains the VkBuffer handle to its index buffer
		vkCmdBindIndexBuffer(commandBuffer, M_Title.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);

		// property .pipelineLayout of a pipeline contains its layout.
		// property .descriptorSets of a descriptor set contains its elements.
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Title.descriptorSets[currentImage],
			0, nullptr);

		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Title.indices.size()), 1, 0, 0, 0);

		//TABLE
		VkBuffer vertexBuffers1[] = { M_Table.vertexBuffer };
		VkDeviceSize offsets1[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers1, offsets1);
		vkCmdBindIndexBuffer(commandBuffer, M_Table.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Table.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Table.indices.size()), 1, 0, 0, 0);

		//TABLE with TANGRAM1
		VkBuffer vertexBuffers2[] = { M_Tangram1.vertexBuffer };
		VkDeviceSize offsets2[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers2, offsets2);
		vkCmdBindIndexBuffer(commandBuffer, M_Tangram1.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Tangram1.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Tangram1.indices.size()), 1, 0, 0, 0);

		//TABLE with TANGRAM2
		VkBuffer vertexBuffers3[] = { M_Tangram2.vertexBuffer };
		VkDeviceSize offsets3[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers3, offsets3);
		vkCmdBindIndexBuffer(commandBuffer, M_Tangram2.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Tangram2.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Tangram2.indices.size()), 1, 0, 0, 0);

		//PIECE1
		VkBuffer vertexBuffers4[] = { M_Piece1.vertexBuffer };
		VkDeviceSize offsets4[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers4, offsets4);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece1.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece1.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece1.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE1
		VkBuffer vertexBuffers5[] = { M_SelectedPiece1.vertexBuffer };
		VkDeviceSize offsets5[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers5, offsets5);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece1.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece1.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece1.indices.size()), 1, 0, 0, 0);

		//PIECE2
		VkBuffer vertexBuffers6[] = { M_Piece2.vertexBuffer };
		VkDeviceSize offsets6[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers6, offsets6);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece2.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece2.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece2.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE2
		VkBuffer vertexBuffers7[] = { M_SelectedPiece2.vertexBuffer };
		VkDeviceSize offsets7[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers7, offsets7);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece2.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece2.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece2.indices.size()), 1, 0, 0, 0);

		//PIECE3
		VkBuffer vertexBuffers8[] = { M_Piece3.vertexBuffer };
		VkDeviceSize offsets8[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers8, offsets8);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece3.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece3.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece3.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE3
		VkBuffer vertexBuffers9[] = { M_SelectedPiece3.vertexBuffer };
		VkDeviceSize offsets9[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers9, offsets9);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece3.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece3.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece3.indices.size()), 1, 0, 0, 0);

		//PIECE4
		VkBuffer vertexBuffers10[] = { M_Piece4.vertexBuffer };
		VkDeviceSize offsets10[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers10, offsets10);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece4.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece4.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece4.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE4
		VkBuffer vertexBuffers11[] = { M_SelectedPiece4.vertexBuffer };
		VkDeviceSize offsets11[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers11, offsets11);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece4.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece4.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece4.indices.size()), 1, 0, 0, 0);

		//PIECE5
		VkBuffer vertexBuffers12[] = { M_Piece5.vertexBuffer };
		VkDeviceSize offsets12[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers12, offsets12);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece5.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece5.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece5.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE5
		VkBuffer vertexBuffers13[] = { M_SelectedPiece5.vertexBuffer };
		VkDeviceSize offsets13[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers13, offsets13);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece5.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece5.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece5.indices.size()), 1, 0, 0, 0);

		//PIECE6
		VkBuffer vertexBuffers14[] = { M_Piece6.vertexBuffer };
		VkDeviceSize offsets14[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers14, offsets14);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece6.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece6.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece6.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE6
		VkBuffer vertexBuffers15[] = { M_SelectedPiece6.vertexBuffer };
		VkDeviceSize offsets15[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers15, offsets15);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece6.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece6.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece6.indices.size()), 1, 0, 0, 0);

		//PIECE6
		VkBuffer vertexBuffers16[] = { M_Piece7.vertexBuffer };
		VkDeviceSize offsets16[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers16, offsets16);
		vkCmdBindIndexBuffer(commandBuffer, M_Piece7.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Piece7.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Piece7.indices.size()), 1, 0, 0, 0);

		//SELECTED PIECE6
		VkBuffer vertexBuffers17[] = { M_SelectedPiece7.vertexBuffer };
		VkDeviceSize offsets17[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers17, offsets17);
		vkCmdBindIndexBuffer(commandBuffer, M_SelectedPiece7.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_SelectedPiece7.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_SelectedPiece7.indices.size()), 1, 0, 0, 0);

		//TRAY
		VkBuffer vertexBuffers18[] = { M_Tray.vertexBuffer };
		VkDeviceSize offsets18[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers18, offsets18);
		vkCmdBindIndexBuffer(commandBuffer, M_Tray.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Tray.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Tray.indices.size()), 1, 0, 0, 0);

		//PLAYBUTTON
		VkBuffer vertexBuffers19[] = { M_PlayButton.vertexBuffer };
		VkDeviceSize offsets19[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers19, offsets19);
		vkCmdBindIndexBuffer(commandBuffer, M_PlayButton.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_PlayButton.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_PlayButton.indices.size()), 1, 0, 0, 0);

		//INSTRUCTIONS
		VkBuffer vertexBuffers20[] = { M_Instructions.vertexBuffer };
		VkDeviceSize offsets20[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers20, offsets20);
		vkCmdBindIndexBuffer(commandBuffer, M_Instructions.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Instructions.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Instructions.indices.size()), 1, 0, 0, 0);

		//WALL
		VkBuffer vertexBuffers21[] = { M_Wall.vertexBuffer };
		VkDeviceSize offsets21[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers21, offsets21);
		vkCmdBindIndexBuffer(commandBuffer, M_Wall.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Wall.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Wall.indices.size()), 1, 0, 0, 0);

		//WALLdx
		VkBuffer vertexBuffers22[] = { M_Walldx.vertexBuffer };
		VkDeviceSize offsets22[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers22, offsets22);
		vkCmdBindIndexBuffer(commandBuffer, M_Walldx.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Walldx.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Walldx.indices.size()), 1, 0, 0, 0);

		//WALLsx
		VkBuffer vertexBuffers23[] = { M_Wallsx.vertexBuffer };
		VkDeviceSize offsets23[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers23, offsets23);
		vkCmdBindIndexBuffer(commandBuffer, M_Wallsx.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Wallsx.descriptorSets[currentImage],
			0, nullptr);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Wallsx.indices.size()), 1, 0, 0, 0);
	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {

		globalUniformBufferObject gubo{};
		UniformBufferObject ubo{};

		void* data;

		//Initial positions of the objects
		gubo.view = glm::lookAt(glm::vec3(0.0f, 7.5f, 10.0f),
			glm::vec3(0.0f, 2.5f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));


		gubo.proj = glm::perspective(glm::radians(45.0f),
			swapChainExtent.width / (float)swapChainExtent.height,
			0.1f, 20.0f);
		gubo.proj[1][1] *= -1;

		vkMapMemory(device, DS_global.uniformBuffersMemory[0][currentImage], 0,
			sizeof(gubo), 0, &data);
		memcpy(data, &gubo, sizeof(gubo));
		vkUnmapMemory(device, DS_global.uniformBuffersMemory[0][currentImage]);

		// Here is where you actually update your uniforms: TITLE
		//still object

		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
			(currentTime - startTime).count();
		static float lastTime = 0.0f;
		float deltaT = time - lastTime;
		lastTime = time;

		static float debounce = time;
		static float ang = 0.0f;

		float ROT_SPEED = 0.65f;
		ang += ROT_SPEED * deltaT;

		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0, 5, 1.0)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(-15.0f),
					glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), ang * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			vkMapMemory(device, DS_Title.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Title.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Title:" << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: TABLE
		//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

			vkMapMemory(device, DS_Table.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Table.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Table:" << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		//Translation matrix used to translate tray and pieces in the center
		static glm::mat4 matTrasl = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		
		static glm::mat4 piecePosInit1 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit2 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit3 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit4 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit5 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit6 = glm::mat4(1.0f);
		static glm::mat4 piecePosInit7 = glm::mat4(1.0f);

		// Here is where you actually update your uniforms: TRAY
		//still object

		{
			UniformBufferObject ubo{};

			glm::mat4 posTray = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.13f, -0.11f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),
					glm::vec3(0.0f, 1.0f, 0.0f));

			ubo.model = matTrasl * posTray;

			vkMapMemory(device, DS_Tray.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Tray.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Tray:" << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: PIECE1
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			piecePosInit1 = matTrasl * posPiece1;

			ubo.model = piecePosInit1;

			vkMapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece1: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE1
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece1: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: PIECE2
		//still object

		{
			UniformBufferObject ubo{};

			glm::mat4 posPiece2 = glm::translate(glm::mat4(1.0f), glm::vec3(2.45f, 0.238f, 1.45f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),
					glm::vec3(0.0f, 1.0f, 0.0f));
			piecePosInit2 = matTrasl * posPiece2;

			ubo.model = piecePosInit2;

			vkMapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece2: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE2
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PIECE3
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece3 = glm::translate(glm::mat4(1.0f), glm::vec3(1.54f, 0.238f, 0.0f));
			piecePosInit3 = matTrasl * posPiece3;

			ubo.model = piecePosInit3;

			vkMapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece3: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE3
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PIECE4
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece4 = glm::translate(glm::mat4(1.0f), glm::vec3(2.43f, 0.238f, -0.57f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),
					glm::vec3(1.0f, 0.0f, 0.0f));
			piecePosInit4 = matTrasl * posPiece4;

			ubo.model = piecePosInit4;

			vkMapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece4: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE4
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PIECE5
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece5 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.238f, 1.0f));
			piecePosInit5 = matTrasl * posPiece5;

			ubo.model = piecePosInit5;

			vkMapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece5: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE5
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PIECE6
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece6 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.01f, 0.238f, 1.62f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),
					glm::vec3(0.0f, 1.0f, 0.0f));
			piecePosInit6 = matTrasl * posPiece6;

			ubo.model = piecePosInit6;

			vkMapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece6: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE6
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PIECE7
		//still object
		{
			UniformBufferObject ubo{};
			glm::mat4 posPiece7 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.238f, -1.09f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),
					glm::vec3(0.0f, 1.0f, 0.0f));
			piecePosInit7 = matTrasl * posPiece7;

			ubo.model = piecePosInit7;

			vkMapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage]);

			//std::cout << "Piece7: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: SELECTED PIECE7
	//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

			vkMapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: PLAYBUTTON
		//still object
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(-0.2, 3, 0.0)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(-15.0f),
					glm::vec3(1.0f, 0.0f, 0.0f));
			vkMapMemory(device, DS_PlayButton.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_PlayButton.uniformBuffersMemory[0][currentImage]);


			//std::cout << "Play: " << std::endl << glm::to_string(ubo.model) << std::endl;
		}

		// Here is where you actually update your uniforms: INSTRUCTIONS 
		//still object 
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));
			vkMapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage]);
		}

		// Here is where you actually update your uniforms: WALL 
		//still object 
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -8.0)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f),
					glm::vec3(1.0f, 0.0f, 0.0f));
			vkMapMemory(device, DS_Wall.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Wall.uniformBuffersMemory[0][currentImage]);
		}


		// Here is where you actually update your uniforms: WALLdx
		//still object 
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(10.0, 0.0, 0.0)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			vkMapMemory(device, DS_Walldx.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Walldx.uniformBuffersMemory[0][currentImage]); }

		// Here is where you actually update your uniforms: WALLsx 
		//still object 
		{
			UniformBufferObject ubo{};
			ubo.model = translate(glm::mat4(1.0f), glm::vec3(-10.0, 0.0, 0.0)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			vkMapMemory(device, DS_Wallsx.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Wallsx.uniformBuffersMemory[0][currentImage]);
		}



		//We have to make changes to the scene once the user is ready to play!

		/*
		Press ENTER to select piece
		A - D : left - right
		W - S : up - down
		E - Q : rotate clockwise - anticlockwise
		Press Z to restart
		Press X to select tangram picture reference
		Press Y to access free play mode
		Press ESC to quit the application
		*/

		static bool play = false;

		if (glfwGetKey(window, GLFW_KEY_SPACE)) {

			if (time - debounce > 0.33) {
				debounce = time;
				play = true;
			}

		}

		//Here you enter in the play mode.

		if (play == true) {
			//TOP VIEW

			gubo.proj = glm::perspective(glm::radians(90.0f),
				swapChainExtent.width / (float)swapChainExtent.height,
				0.1f, 20.0f);
			gubo.proj[1][1] *= -1;

			gubo.view = glm::translate(
				glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1, 0, 0)),
				glm::vec3(0, -5, 0));

			vkMapMemory(device, DS_global.uniformBuffersMemory[0][currentImage], 0,
				sizeof(gubo), 0, &data);
			memcpy(data, &gubo, sizeof(gubo));
			vkUnmapMemory(device, DS_global.uniformBuffersMemory[0][currentImage]);


			// Here is where you actually update your uniforms: PLAIN TABLE (exits the visible screen)
			{ UniformBufferObject ubo{};
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
			vkMapMemory(device, DS_Table.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Table.uniformBuffersMemory[0][currentImage]); }


			// Here is where you actually update your uniforms: INSTRUCTIONS (enter the visible screen) //Istruzioni da fare direttamente sul tavolo come texture.
			{ UniformBufferObject ubo{};
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			vkMapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage]); }


			// Here is where you actually update your uniforms: TITLE (it must exit the screen)
			{ UniformBufferObject ubo{};
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
			vkMapMemory(device, DS_Title.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Title.uniformBuffersMemory[0][currentImage]); }

			// Here is where you actually update your uniforms: TRAY (it must exit the screen)
			{ UniformBufferObject ubo{};
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
			vkMapMemory(device, DS_Tray.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Tray.uniformBuffersMemory[0][currentImage]); }

			// Here is where you actually update your uniforms: PLAYBUTTON (it must exit the screen)
			{ UniformBufferObject ubo{};
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
			vkMapMemory(device, DS_PlayButton.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_PlayButton.uniformBuffersMemory[0][currentImage]); }




			static int state = 0;   //0 - initial situation /pieces in the center of the screen
									//1 - first click - Tangram1
									//2 - second click - Tangram2
			static bool freePlayMode = true; //gamer plays without tangram pictures example


			//gamer clicks y to return to play without tangram picture example
			if (glfwGetKey(window, GLFW_KEY_Y)) {
				if (time - debounce > 0.33) {
					debounce = time;
					freePlayMode = true;
					state = 0;
				}
			}
			//gamer clicks y to return to play without tangram picture example
			if (freePlayMode = true) {

				//tangram1 table must exit the screen
				{UniformBufferObject ubo{};
				ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				vkMapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage]); }

				//tangra2 table must exit the screen
				{UniformBufferObject ubo{};
				ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				vkMapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage]); }

				// Here is where you actually update your uniforms: no TANGRAM picture example

				{UniformBufferObject ubo{};
				ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
				vkMapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage]); }
			}



			//gamer clicks x to play with tangram picture example
			if (glfwGetKey(window, GLFW_KEY_X)) {
				if (time - debounce > 0.33) {
					debounce = time;
					state++;
					freePlayMode = false;
				}
			}
			//gamer clicks x to play with tangram picture example
			if (state % 2 != 0) {

				if (state == 1) {
					//instruction table must exit the screen
					{UniformBufferObject ubo{};
					ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					vkMapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Instructions.uniformBuffersMemory[0][currentImage]); }

				}
				else {
					//tangram2 table must exit the screen
					{UniformBufferObject ubo{};
					ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					vkMapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage]); }
				}

				// Here is where you actually update your uniforms: TABLE --> texture Tangram1
				{UniformBufferObject ubo{};
				ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

				vkMapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage]); }

			}
			else if (state != 0 && state % 2 == 0) {

				//tangram1 table must exit the screen
				{UniformBufferObject ubo{};
				ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				vkMapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Tangram1.uniformBuffersMemory[0][currentImage]); }


				// Here is where you actually update your uniforms: TABLE --> texture Tangram2
				{UniformBufferObject ubo{};
				ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

				vkMapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage], 0,
					sizeof(ubo), 0, &data);
				memcpy(data, &ubo, sizeof(ubo));
				vkUnmapMemory(device, DS_Tangram2.uniformBuffersMemory[0][currentImage]); }
			}

			//press ENTER to select piece (which brightens)
			static bool restart = false;
			static int selectedPiece = 0;

			static glm::mat4 piecePosCurrent1 = piecePosInit1;
			static glm::mat4 piecePosCurrent2 = piecePosInit2;
			static glm::mat4 piecePosCurrent3 = piecePosInit3;
			static glm::mat4 piecePosCurrent4 = piecePosInit4;
			static glm::mat4 piecePosCurrent5 = piecePosInit5;
			static glm::mat4 piecePosCurrent6 = piecePosInit6;
			static glm::mat4 piecePosCurrent7 = piecePosInit7;


			static float rotation1 = 0.0f;
			static float rotation2 = -90.0f;
			static float rotation3 = 0.0f;
			static float rotation4 = 0.0f;
			static float rotation5 = 0.0f;
			static float rotation6 = 180.0f;
			static float rotation7 = 180.0f;



			if (glfwGetKey(window, GLFW_KEY_KP_ENTER)) {
				if (time - debounce > 0.33) {
					debounce = time;
					if (selectedPiece == 7) {
						selectedPiece = 1;
					}
					else {
						selectedPiece += 1;
					}
					restart = false;
				}

			}

			static glm::mat4 updateSelectedPiece1 = glm::mat4(1.0f);
			static glm::mat4 updatePiece1 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece2 = glm::mat4(1.0f);
			static glm::mat4 updatePiece2 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece3 = glm::mat4(1.0f);
			static glm::mat4 updatePiece3 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece4 = glm::mat4(1.0f);
			static glm::mat4 updatePiece4 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece5 = glm::mat4(1.0f);
			static glm::mat4 updatePiece5 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece6 = glm::mat4(1.0f);
			static glm::mat4 updatePiece6 = glm::mat4(1.0f);

			static glm::mat4 updateSelectedPiece7 = glm::mat4(1.0f);
			static glm::mat4 updatePiece7 = glm::mat4(1.0f);


			if (selectedPiece == 1) {
				piecePosCurrent1 = updatePiecePos(piecePosCurrent1, selectedPiece, window);
				rotation1 = updateRotation(rotation1, selectedPiece, window);
				updateSelectedPiece1 = piecePosCurrent1 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation1), glm::vec3(0, 1, 0));
				updatePiece1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece7 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent7 == piecePosInit7) {
					updatePiece7 = piecePosCurrent7;
				}
				else {
					updatePiece7 = piecePosCurrent7 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation7), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 1) {
				if (piecePosCurrent1 == piecePosInit1) {
					updateSelectedPiece1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece1 = piecePosCurrent1;
				}
				else {
					updateSelectedPiece1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece1 = piecePosCurrent1 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation1), glm::vec3(0, 1, 0));
				}
			}


			if (selectedPiece == 2) {
				piecePosCurrent2 = updatePiecePos(piecePosCurrent2, selectedPiece, window);
				rotation2 = updateRotation(rotation2, selectedPiece, window);
				updateSelectedPiece2 = piecePosCurrent2 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation2), glm::vec3(0, 1, 0));
				updatePiece2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent1 == piecePosInit1) {
					updatePiece1 = piecePosCurrent1;
				}
				else {
					updatePiece1 = piecePosCurrent1 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation1), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 2) {
				if (piecePosCurrent2 == piecePosInit2) {
					updateSelectedPiece2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece2 = piecePosCurrent2;
				}
				else {
					updateSelectedPiece2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece2 = piecePosCurrent2 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation2), glm::vec3(0, 1, 0));
				}
			}


			if (selectedPiece == 3) {
				piecePosCurrent3 = updatePiecePos(piecePosCurrent3, selectedPiece, window);
				rotation3 = updateRotation(rotation3, selectedPiece, window);
				updateSelectedPiece3 = piecePosCurrent3 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation3), glm::vec3(0, 1, 0));
				updatePiece3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent2 == piecePosInit2) {
					updatePiece2 = piecePosCurrent2;
				}
				else {
					updatePiece2 = piecePosCurrent2 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation2), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 3) {
				if (piecePosCurrent3 == piecePosInit3) {
					updateSelectedPiece3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece3 = piecePosCurrent3;
				}
				else {
					updateSelectedPiece3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece3 = piecePosCurrent3 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation3), glm::vec3(0, 1, 0));
				}
			}


			if (selectedPiece == 4) {
				piecePosCurrent4 = updatePiecePos(piecePosCurrent4, selectedPiece, window);
				rotation4 = updateRotation(rotation4, selectedPiece, window);
				updateSelectedPiece4 = piecePosCurrent4 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation4), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0));
				updatePiece4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent3 == piecePosInit3) {
					updatePiece3 = piecePosCurrent3;
				}
				else {
					updatePiece3 = piecePosCurrent3 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation3), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 4) {
				if (piecePosCurrent4 == piecePosInit4) {
					updateSelectedPiece4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece4 = piecePosCurrent4;
				}
				else {
					updateSelectedPiece4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece4 = piecePosCurrent4 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation4), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0));
				}
			}


			if (selectedPiece == 5) {
				piecePosCurrent5 = updatePiecePos(piecePosCurrent5, selectedPiece, window);
				rotation5 = updateRotation(rotation5, selectedPiece, window);
				updateSelectedPiece5 = piecePosCurrent5 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation5), glm::vec3(0, 1, 0));
				updatePiece5 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent4 == piecePosInit4) {
					updatePiece4 = piecePosCurrent4;
				}
				else {
					updatePiece4 = piecePosCurrent4 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation4), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0));
				}
			}
			else if (selectedPiece != 5) {
				if (piecePosCurrent5 == piecePosInit5) {
					updateSelectedPiece5 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece5 = piecePosCurrent5;
				}
				else {
					updateSelectedPiece5 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece5 = piecePosCurrent5 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation5), glm::vec3(0, 1, 0));
				}
			}


			if (selectedPiece == 6) {
				piecePosCurrent6 = updatePiecePos(piecePosCurrent6, selectedPiece, window);
				rotation6 = updateRotation(rotation6, selectedPiece, window);
				updateSelectedPiece6 = piecePosCurrent6 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation6), glm::vec3(0, 1, 0));
				updatePiece6 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece5 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent5 == piecePosInit5) {
					updatePiece5 = piecePosCurrent5;
				}
				else {
					updatePiece5 = piecePosCurrent5 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation5), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 6) {
				if (piecePosCurrent6 == piecePosInit6) {
					updateSelectedPiece6 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece6 = piecePosCurrent6;
				}
				else {
					updateSelectedPiece6 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece6 = piecePosCurrent6 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation6), glm::vec3(0, 1, 0));
				}
			}


			if (selectedPiece == 7) {
				piecePosCurrent7 = updatePiecePos(piecePosCurrent7, selectedPiece, window);
				rotation7 = updateRotation(rotation7, selectedPiece, window);
				updateSelectedPiece7 = piecePosCurrent7 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation7), glm::vec3(0, 1, 0));
				updatePiece7 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				updateSelectedPiece6 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
				if (piecePosCurrent6 == piecePosInit6) {
					updatePiece6 = piecePosCurrent6;
				}
				else {
					updatePiece6 = piecePosCurrent6 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation6), glm::vec3(0, 1, 0));
				}
			}
			else if (selectedPiece != 7) {
				if (piecePosCurrent7 == piecePosInit7) {
					updateSelectedPiece7 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece7 = piecePosCurrent7;
				}
				else {
					updateSelectedPiece7 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -7.0f, 0.0f));
					updatePiece7 = piecePosCurrent7 * glm::rotate(glm::mat4(1.0f), glm::radians(rotation7), glm::vec3(0, 1, 0));
				}
			}

			
			//Store the updated positions of pieces (both 'selected' and not selected)

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece1;

			/*
				//COLLISION DETECTION, funzione da richiamare per tutti i 7 pezzi!
				//Il giocatore seleziona un pezzo a sua scelta, lo trasla e/o ruota nella posizione che preferisce, anche accavallandosi ad un altro pezzo.
				//Alla fine dell'imposizione della traslazione/rotazione il pezzo rimane dove è se non compenetra altri pezzi
				//mentre se c'è collision viene spostato nella posizione corretta più vicina


				//assegno a ubo.model una matrice di rotazione il cui valore dipende dal verificarsi o no della collision
				//hasCollision ritorna updateSelectedPiece1 se non è avvenuta collisione (il pezzo rimane dove l'ho spostato)
				//hasCollision ritorna una nuova matrice di rotazione se è avvenuta collisione (il pezzo si sposta della posizione corretta più vicina)

				ubo.model = hasCollision(selectedPiece, M_SelectedPiece1.vertices, updateSelectedPiece1);
			*/

			vkMapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece1;
			vkMapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece2;
			vkMapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece2;
			vkMapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece3;
			vkMapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece3;
			vkMapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece4;
			vkMapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece4;
			vkMapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece5;
			vkMapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece5;
			vkMapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece6;
			vkMapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece6;
			vkMapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updateSelectedPiece7;
			vkMapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage]); }

			{UniformBufferObject ubo{};
			ubo.model = updatePiece7;
			vkMapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage]); }



			//gamer wants to restart game

			if (glfwGetKey(window, GLFW_KEY_Z)) {
				if (time - debounce > 0.33) {
					debounce = time;
					restart = true; //pieces return to inital positions
					selectedPiece = 0; //no objet is brighten (no object is selected)
					piecePosCurrent1 = piecePosInit1;
					piecePosCurrent2 = piecePosInit2;
					piecePosCurrent3 = piecePosInit3;
					piecePosCurrent4 = piecePosInit4;
					piecePosCurrent5 = piecePosInit5;
					piecePosCurrent6 = piecePosInit6;
					piecePosCurrent7 = piecePosInit7;

					rotation1 = 0.0f;
					rotation2 = -90.0f;
					rotation3 = 0.0f;
					rotation4 = 0.0f;
					rotation5 = 0.0f;
					rotation6 = 180.0f;
					rotation7 = 180.0f;

				}
			}

			if (restart == true) {

				// Here is where you actually update your uniforms: PIECE1
				//still object
				{
					UniformBufferObject ubo{};
					ubo.model = piecePosInit1;

					vkMapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece1.uniformBuffersMemory[0][currentImage]);

				}

				// Here is where you actually update your uniforms: SELECTED PIECE1
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece1.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE2
				//still object
				{
					UniformBufferObject ubo{};

					ubo.model = piecePosInit2;

					vkMapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece2.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: SELECTED PIECE2
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece2.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE3
				//still object
				{
					UniformBufferObject ubo{};
					ubo.model = piecePosInit3;

					vkMapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece3.uniformBuffersMemory[0][currentImage]);

				}

				// Here is where you actually update your uniforms: SELECTED PIECE3
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece3.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE4
				//still object
				{
					UniformBufferObject ubo{};

					ubo.model = piecePosInit4;

					vkMapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece4.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: SELECTED PIECE4
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece4.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE5
				//still object
				{
					UniformBufferObject ubo{};
					ubo.model = piecePosInit5;

					vkMapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece5.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: SELECTED PIECE5
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece5.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE6
				//still object
				{
					UniformBufferObject ubo{};

					ubo.model = piecePosInit6;

					vkMapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece6.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: SELECTED PIECE6
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece6.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: PIECE7
				//still object
				{
					UniformBufferObject ubo{};

					ubo.model = piecePosInit7;

					vkMapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_Piece7.uniformBuffersMemory[0][currentImage]);
				}

				// Here is where you actually update your uniforms: SELECTED PIECE7
			//still object
				{
					UniformBufferObject ubo{};
					ubo.model = translate(glm::mat4(1.0f), glm::vec3(0.0, -5, 0.0));

					vkMapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage], 0,
						sizeof(ubo), 0, &data);
					memcpy(data, &ubo, sizeof(ubo));
					vkUnmapMemory(device, DS_SelectedPiece7.uniformBuffersMemory[0][currentImage]);
				}

			}
		}

	}


	//function to detect collisions

	/*

	//gli argomenti della funzione hasCollision sono:
					// int i (identificatore del pezzo selezionato di cui si verificano le collision con tutti gli altri pezzi)
					// std::vector<Vertex> vertices (i 3 vertici alla base del pezzo 1 per i quali bisogna verificare le collision)
					// glm::mat4 updatePos (la matrice di rotazione del pezzo alla fine del movimento imposto dall'utente e prima di verificare la collision)

	glm::mat4 hasCollision(int i, std::vector<Vertex> vertices, glm::mat4 updatePos) {

		//si definiscono i vettori  dei vertici alla base di tutti i pezzi (valori sempre aggiornati alla posizione corrente)
		//per parallelogramma e quadrato si contando due triangoli da 3 vertici ciascuno, si trattano come due triadi di posizioni diverse
		std::vector <glm::vec3> v1 = { M_Piece1.vertices[? ].pos, M_Piece1.vertices[? ].pos, M_Piece1.vertices[? ].pos };
		std::vector <glm::vec3>  v2 = { M_Piece2.vertices[? ].pos, M_Piece2.vertices[? ].pos, M_Piece2.vertices[? ].pos };
		std::vector <glm::vec3>  v3 = { M_Piece3.vertices[? ].pos, M_Piece3.vertices[? ].pos, M_Piece3.vertices[? ].pos };
		std::vector <glm::vec3>  v4_1 = { M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos };   //1° triangolo parallelogramma
		std::vector <glm::vec3>  v4_2 = { M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos, M_Piece4.vertices[? ].pos };   //2° triangoloparallelogramma
		std::vector <glm::vec3>  v5_1 = { M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos };   //1° triangolo quadrato
		std::vector <glm::vec3>  v5_2 = { M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos, M_Piece5.vertices[? ].pos };   //2° triangolo quadrato
		std::vector <glm::vec3>  v6 = { M_Piece6.vertices[? ].pos, M_Piece6.vertices[? ].pos, M_Piece6.vertices[? ].pos };
		std::vector <glm::vec3>  v7 = { M_Piece7.vertices[? ].pos, M_Piece7.vertices[? ].pos, M_Piece7.vertices[? ].pos };


		//si definisce il vettore vert contenente le posizioni x, y, z dei vertici della base del pezzo di cui verifichiamo le collisions
		//nel caso di parallelogramma e quadrato sono 6 vertici (due triangoli), si riporta solo il caso base del triangolo

		std::vector <glm::vec3> vert = { vertices[?].pos, vertices[?].pos, vertices[?].pos };

		if (i == 1) { //da ripetere per tutti i pezzi (1 <= i <= 7, i = selectedPieces (quello che il giocatore ha appena mosso) )

			//ad ogni vertice del pezzo mosso viene applicato lo stesso algoritmo, collision detection con tutti i pezzi
			for (glm::vec3 v : vert) {

				//collision con il Piece2 - algorithm reference https://youtu.be/HYAgJN3x4GA
				float w1_2 = (v2[0].x * (v2[2].z - v2[0].z) + (v.z - v2[0].z) * (v2[2].x - v2[0].x) - v.x*(v2[2].z - v2[0].z)) / ((v2[1].z - v2[0].z) * (v2[2].x - v2[0].x) - (v2[1].x - v2[0].x) * (v2[2].z - v2[0].z));
				float w2_2 = (v.z - v2[0].z - w1_2 * (v2[1].z - v2[0].z)) / (v2[2].z - v2[0].z);

				if (w1_2 >= 0 && w2_2 >= 0 && w1_2 + w2_2 <= 1) { //c'è la collision!!!!!!
					return newPos;	//si ritorna una matrice di rotazione che posiziona il pezzo nella prima posizione corretta disponibile
				}

				//collision con il piece3
				float w1_3 = (v3[0].x * (v3[2].z - v3[0].z) + (v.z - v3[0].z) * (v3[2].x - v3[0].x) - v.x*(v3[2].z - v3[0].z)) / ((v3[1].z - v3[0].z) * (v3[2].x - v3[0].x) - (v3[1].x - v3[0].x) * (v3[2].z - v3[0].z));
				float w2_3 = (v.z - v3[0].z - w1_3 * (v3[1].z - v3[0].z)) / (v3[2].z - v3[0].z);

				if (w1_3 >= 0 && w2_3 >= 0 && w1_3 + w2_3 <= 1) { //c'è la collision!!!!!!
					return newPos;	//si ritorna una matrice di rotazione che posiziona il pezzo nella prima posizione corretta disponibile
				}


				//Collision con 4 è un parallelogramma, si tratta come due triangoli


				//Collision con 5 è un quadrato si tratta come due triangoli



				float w1_6 = (v6[0].x * (v6[2].z - v6[0].z) + (v.z - v6[0].z) * (v6[2].x - v6[0].x) - v.x*(v6[2].z - v6[0].z)) / ((v6[1].z - v6[0].z) * (v6[2].x - v6[0].x) - (v6[1].x - v6[0].x) * (v6[2].z - v6[0].z));
				float w2_6 = (v.z - v6[0].z - w1_6 * (v6[1].z - v6[0].z)) / (v6[2].z - v6[0].z);

				if (w1_6 >= 0 && w2_6 >= 0 && w1_6 + w2_6 <= 1) { //c'è la collision!!!!!!
					return newPos;	//si ritorna una matrice di rotazione che posiziona il pezzo nella prima posizione corretta disponibile
				}

				float w1_7 = (v7[0].x * (v7[2].z - v7[0].z) + (v.z - v7[0].z) * (v7[2].x - v7[0].x) - v.x*(v7[2].z - v7[0].z)) / ((v7[1].z - v7[0].z) * (v7[2].x - v7[0].x) - (v7[1].x - v7[0].x) * (v7[2].z - v7[0].z));
				float w2_7 = (v.z - v7[0].z - w1_7 * (v7[1].z - v7[0].z)) / (v7[2].z - v7[0].z);

				if (w1_7 >= 0 && w2_7 >= 0 && w1_7 + w2_7 <= 1) { //c'è la collision!!!!!!
					return newPos;	//si ritorna una matrice di rotazione che posiziona il pezzo nella prima posizione corretta disponibile
				}

				//se arrivo fin qui non c'è mai stata alcuna collision con nessun pezzo! --> devo ritornare la matrice di rotazione iniziale!

				return updatePos;

			}
		}
	}



	//IN ALTERNATIVA algorithm reference http://www.jeffreythompson.org/collision-detection/tri-point.php

	//given the pieces' base vertices, to test if a point is inside a triangle,
	//we compare the area of the original triangle with the sum of the area of three triangles made between the point and the corners of the triangle.

	//To get the area, we use Heron’s Forumula:

		float areaOrig = abs( (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );

	//We need to calculate the area of the three triangles made from the point as well:

		float area1 =    abs( (x1-px)*(y2-py) - (x2-px)*(y1-py) );
		float area2 =    abs( (x2-px)*(y3-py) - (x3-px)*(y2-py) );
		float area3 =    abs( (x3-px)*(y1-py) - (x1-px)*(y3-py) );

	//If we add the three areas together and they equal the original, we know we’re inside the triangle! Using this, we can test for collision:

		if (area1 + area2 + area3 == areaOrig) {
			return newPos;  //collision detected!
		}
		return currentPos;


	*/

	//function to translate/rotate piece with keyboard

	float updateRotation(float rotation, int i, GLFWwindow* window) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		static float lastTime = 0.0f;
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
			(currentTime - startTime).count();

		float deltaT = time - lastTime;
		lastTime = time;
		static float debounce = time;

		static bool clockwiseRotation = false;
		static bool anticlockwiseRotation = false;

		static float rot[7];
		rot[i - 1] = rotation;

		if (glfwGetKey(window, GLFW_KEY_E)) {
			if (time - debounce > 0.33) {
				debounce = time;
				clockwiseRotation = true;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_Q)) {
			if (time - debounce > 0.33) {
				debounce = time;
				anticlockwiseRotation = true;
			}
		}

		if (clockwiseRotation == true) {
			rot[i - 1] -= 45.0f;
		}
		clockwiseRotation = false;

		if (anticlockwiseRotation == true) {
			rot[i - 1] += 45.0f;
		}
		anticlockwiseRotation = false;

		return rot[i - 1];
	}


	glm::mat4 updatePiecePos(glm::mat4 piecePos, int i, GLFWwindow* window) {

		static auto startTime = std::chrono::high_resolution_clock::now();
		static float lastTime = 0.0f;
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
			(currentTime - startTime).count();

		float deltaT = time - lastTime;
		lastTime = time;


		static float piecePosInit[3][7];
		//i è il num del pezzo (in ingresso nella funzione) 
		piecePosInit[i - 1][0] = piecePos[3][0];
		piecePosInit[i - 1][1] = piecePos[3][1];
		piecePosInit[i - 1][2] = piecePos[3][2];


		glm::mat3 dir = glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f))) *
			glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f))) *
			glm::mat3(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
		
		const float MOVE_SPEED = 1.75f;

		//go left
		if (glfwGetKey(window, GLFW_KEY_A)) {

			glm::vec3 transition = MOVE_SPEED * glm::vec3(dir[0]) * deltaT;
			piecePosInit[i - 1][0] -= transition[0];
			piecePosInit[i - 1][1] -= transition[1];
			piecePosInit[i - 1][2] -= transition[2];

		}
		//go right
		if (glfwGetKey(window, GLFW_KEY_D)) {

			glm::vec3 transition = MOVE_SPEED * glm::vec3(dir[0]) * deltaT;
			piecePosInit[i - 1][0] += transition[0];
			piecePosInit[i - 1][1] += transition[1];
			piecePosInit[i - 1][2] += transition[2];
		}
		//go down
		if (glfwGetKey(window, GLFW_KEY_S)) {
			glm::vec3 transition = MOVE_SPEED * glm::vec3(dir[2]) * deltaT;
			piecePosInit[i - 1][0] += transition[0];
			piecePosInit[i - 1][1] += transition[1];
			piecePosInit[i - 1][2] += transition[2];
		}
		//go up
		if (glfwGetKey(window, GLFW_KEY_W)) {
			glm::vec3 transition = MOVE_SPEED * glm::vec3(dir[2]) * deltaT;
			piecePosInit[i - 1][0] -= transition[0];
			piecePosInit[i - 1][1] -= transition[1];
			piecePosInit[i - 1][2] -= transition[2];
		}

		return glm::translate(glm::mat4(1.0f), glm::vec3(piecePosInit[i - 1][0], piecePosInit[i - 1][1], piecePosInit[i - 1][2]));
	}

};

// This is the main: probably you do not need to touch this!
int main() {
	MyProject app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}