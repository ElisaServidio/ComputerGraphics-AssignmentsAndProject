// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;

int k;

//__CUBE__
void make_vert(glm::vec3 vecPos, glm::vec3 normal, glm::vec2 uv) {
	M1_vertices[k].pos = vecPos;
	M1_vertices[k].norm = normal;
	M1_vertices[k].UV = uv;
	k++;
}

void make_face(int v1, int v2, int v3) {
	M1_indices[k++] = v1;
	M1_indices[k++] = v2;
	M1_indices[k++] = v3;
}
void make_face(int v1, int v2, int v3, int v4) {
	make_face(v1, v2, v3);
	make_face(v4, v3, v1);
}


//__CYLINDER__

void make_vert1(glm::vec3 vecPos, glm::vec3 normal, glm::vec2 uv) {
	M2_vertices[k].pos = vecPos;
	M2_vertices[k].norm = normal;
	M2_vertices[k].UV = uv;
	k++;
}


void make_vert2(glm::vec3 vecPos, glm::vec2 uv) {
	M2_vertices[k].pos = vecPos;
	vecPos.y = 0.0f;
	M2_vertices[k].norm = glm::normalize(vecPos);
	M2_vertices[k].UV = uv;
	k++;
}


void make_face2(int v1, int v2, int v3) {
	M2_indices[k++] = v1;
	M2_indices[k++] = v2;
	M2_indices[k++] = v3;
}




void makeModels() {


//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
M1_vertices.resize(4*6);
k = 0; //reset index k

glm::vec3 normal;
glm::vec2 uv;


glm::vec3 front_bot_L = glm::vec3(-1.0, -1.0, -1.0);
glm::vec3 front_bot_R = glm::vec3( 1.0, -1.0, -1.0);
glm::vec3 front_top_R = glm::vec3( 1.0,  1.0, -1.0);
glm::vec3 front_top_L = glm::vec3(-1.0,  1.0, -1.0);

glm::vec3 back_bot_L = glm::vec3(-1.0, -1.0, 1.0);
glm::vec3 back_bot_R = glm::vec3( 1.0, -1.0, 1.0);
glm::vec3 back_top_R = glm::vec3( 1.0,  1.0, 1.0);
glm::vec3 back_top_L = glm::vec3(-1.0,  1.0, 1.0);




//front
normal = glm::vec3(0.0, 0.0, -1.0);
uv = glm::vec2(0.25, 0.0);
make_vert(front_bot_L, normal, uv); //0
uv = glm::vec2(0.125, 0.0);
make_vert(front_bot_R, normal, uv); //1
uv = glm::vec2(0.125, 0.125);
make_vert(front_top_R, normal, uv); //2
uv = glm::vec2(0.25, 0.125);
make_vert(front_top_L, normal, uv); //3

//back 
normal = glm::vec3(0.0, 0.0, 1.0);
uv = glm::vec2(0.25, 0.375);
make_vert(back_bot_L, normal, uv); //4
uv = glm::vec2(0.125, 0.375);
make_vert(back_bot_R, normal, uv); //5
uv = glm::vec2(0.125, 0.25);
make_vert(back_top_R, normal, uv); //6
uv = glm::vec2(0.25, 0.25);
make_vert(back_top_L, normal, uv); //7

//roof
normal = glm::vec3(0.0, 1.0, 0.0);
uv = glm::vec2(0.25, 0.125);
make_vert(front_top_L, normal, uv); //8
uv = glm::vec2(0.125, 0.125);
make_vert(front_top_R, normal, uv); //9
uv = glm::vec2(0.25, 0.25);
make_vert(back_top_L,  normal, uv);  //10
uv = glm::vec2(0.125, 0.25);
make_vert(back_top_R,  normal, uv);  //11

//floor 
normal = glm::vec3(0.0, -1.0, 0.0);
uv = glm::vec2(0.25, 0.5);
make_vert(front_bot_L, normal, uv); //12
uv = glm::vec2(0.125, 0.5);
make_vert(front_bot_R, normal, uv); //13
uv = glm::vec2(0.25, 0.375);
make_vert(back_bot_L,  normal, uv);  //14
uv = glm::vec2(0.125, 0.375);
make_vert(back_bot_R,  normal, uv);  //15

//left 
normal = glm::vec3(-1.0, 0.0, 0.0);
uv = glm::vec2(0.375, 0.375);
make_vert(front_bot_L, normal, uv); //16
uv = glm::vec2(0.375, 0.25);
make_vert(front_top_L, normal, uv); //17
uv = glm::vec2(0.25, 0.375);
make_vert(back_bot_L,  normal, uv);  //18
uv = glm::vec2(0.25, 0.25);
make_vert(back_top_L,  normal, uv);  //19

//right 
normal = glm::vec3(1.0, 0.0, 0.0);
uv = glm::vec2(0.0, 0.375);
make_vert(front_bot_R, normal, uv); //20
uv = glm::vec2(0.0, 0.25);
make_vert(front_top_R, normal, uv); //21
uv = glm::vec2(0.125, 0.375);
make_vert(back_bot_R,  normal, uv);  //22
uv = glm::vec2(0.125, 0.25);
make_vert(back_top_R,  normal, uv);  //23



// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M1_indices.resize(3 * 12);
k = 0; //reset index k

make_face(0,   1,  2,  3);	//	front
make_face(4,   5,  6,  7);	//	back
make_face(8,   9, 11, 10);	//	roof
make_face(12, 13, 15, 14);	//	floor
make_face(16, 17, 19, 18);	//	left
make_face(20, 21, 23, 22);	//	right


//// M2 : Cylinder
// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices

float radius = 1.0;
int NSlices = 72;
float height = 2.0;

float angle = glm::radians(360.0 / NSlices);

M2_vertices.resize( 4 + (4 * NSlices));
k = 0; //reset index k

make_vert1(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec2(0.875, 0.125));	//bottom center
make_vert1(glm::vec3(0.0, height, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.625, 0.125));	//top center

glm::vec3 vecPos;
float r = 0.125;

// Vertices definitions
normal = glm::vec3(0.0, -1.0, 0.0);
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radius * glm::cos(angle * i), 0.0, radius * glm::sin(angle * i));
	uv = glm::vec2(r * glm::cos(angle * i) + 0.875, r * glm::sin(angle * i) + 0.125);
	make_vert1(vecPos, normal, uv);
}

/*vecPos = glm::vec3(radius * glm::cos(angle * 0.0), 0.0, radius * glm::sin(angle * 0.0));
uv = glm::vec2(1, 0.5);
make_vert1(vecPos, normal, uv);*/

normal = glm::vec3(0.0, 1.0, 0.0);
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radius * glm::cos(angle * i), height, radius * glm::sin(angle * i));
	uv = glm::vec2(r * glm::cos(angle * i) + 0.625, r * glm::sin(angle * i) + 0.125);
	make_vert1(vecPos, normal, uv);
}

/*vecPos = glm::vec3(radius * glm::cos(angle * 0.0), height, radius * glm::sin(angle * 0.0));
uv = glm::vec2(1, 0.25);
make_vert1(vecPos, normal, uv);*/

float j = 0.0;
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radius * glm::cos(angle * i), 0.0, radius * glm::sin(angle * i));
	uv = glm::vec2(0.5 + j, 0.5);
	j += 0.5 / NSlices;
	make_vert2(vecPos, uv);
}

vecPos = glm::vec3(radius * glm::cos(angle * 0.0), 0.0, radius * glm::sin(angle * 0.0));
uv = glm::vec2(1, 0.5);
make_vert2(vecPos, uv);

j = 0.0;
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radius * glm::cos(angle * i), height, radius * glm::sin(angle * i));
	uv = glm::vec2(0.5 + j, 0.25);
	j += 0.5 / NSlices;
	make_vert2(vecPos, uv);
}

vecPos = glm::vec3(radius * glm::cos(angle * 0.0), height, radius * glm::sin(angle * 0.0));
uv = glm::vec2(1, 0.25);
make_vert2(vecPos, uv);



// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)

M2_indices.resize( 3 * (4 * NSlices+1) );

// indices definitions
k = 0; //reset index k

int bottom_center = 0;
int top_center = 1;
int first = 2;
int last = NSlices + 1;

//floor
for (int i = 0; i < NSlices; i++)
{	
	if (i == 0) {
		make_face2( bottom_center, first, last);
	} else {
		int nxt = i + first;
		make_face2(bottom_center, nxt-1, nxt);
	}
}

first += NSlices;
last  += NSlices;

//roof
for (int i = 0; i < NSlices; i++)
{
	if (i == 0) {
		make_face2(top_center, first, last);
	} else {
		int nxt = i + first;
		make_face2(top_center, nxt-1, nxt);
	}
}

first += NSlices;
last  += NSlices;

//walls

//tris from roof to bottom 
for (int i = 0; i < NSlices; i++)
{
	if (i == 0) {
		make_face2(first + 2*NSlices + 1, first + NSlices, last);
	} else {
		int nxt = i + first;
		make_face2(nxt + NSlices + 1, nxt-1, nxt);
	}
}

first += NSlices;
last  += NSlices;

//tris from bottom to roof
for (int i = 0; i < NSlices; i++)
{
	if (i == 0) {
		make_face2(last - NSlices, first + NSlices + 1, last + 1);
	} else {
		int nxt = i + first;
		make_face2(nxt - NSlices -1, nxt, nxt + 1);
	}
}

}
