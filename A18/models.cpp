// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

int k;

//__CUBE__
void make_vert(glm::vec3 vecPos, glm::vec3 normal) {
	M1_vertices[k].pos = vecPos;
	M1_vertices[k].norm = normal;
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
void make_vert2(glm::vec3 vecPos) {
	M2_vertices[k].pos = vecPos;
	vecPos.y = 0.0f;
	M2_vertices[k].norm = glm::normalize(vecPos);
	k++;
}
void make_vert2(glm::vec3 vecPos, glm::vec3 normal) {
	M2_vertices[k].pos = vecPos;
	M2_vertices[k].norm = normal;
	k++;
}

void make_face2(int v1, int v2, int v3) {
	M2_indices[k++] = v1;
	M2_indices[k++] = v2;
	M2_indices[k++] = v3;
}

//__SPHERE__
void make_vert3( double x, double y, double z) {
	glm::vec3 vertPos = glm::vec3(x, y, z);
	M3_vertices[k].pos = vertPos;
	M3_vertices[k].norm = glm::normalize(vertPos); //point straight out (useful for sphere)
	k++;
}

void make_face3(int v1, int v2, int v3) {
	M3_indices[k++] = v1;
	M3_indices[k++] = v2;
	M3_indices[k++] = v3;
}
void update_xyz(float r, float hang, float vang, float* x, float* y, float* z) {
	vang = glm::radians(vang);
	hang = glm::radians(hang);
	x[0] = r * cos(hang) * sin(vang);	// R * cosv * cosu
	z[0] = r * sin(hang) * sin(vang);	// R * sinv * cosu
	y[0] = r * cos(vang);				// R * cosu
}

//__SPRING__
void make_vert4(glm::vec3 vertPos, glm::vec3 loopcenter) {
	M4_vertices[k].pos = vertPos;
	M4_vertices[k].norm = glm::normalize(vertPos - loopcenter); //point straight out from loopcenter
	k++;
}

void make_face4(int v1, int v2, int v3) {
	M4_indices[k++] = v1;
	M4_indices[k++] = v2;
	M4_indices[k++] = v3;
}
void make_face4(int v1, int v2, int v3, int v4) {
	make_face4(v1, v2, v3);
	make_face4(v4, v3, v1);
}






void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
M1_vertices.resize(4*6);
k = 0; //reset index k

glm::vec3 normal;

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
make_vert(front_bot_L, normal); //0
make_vert(front_bot_R, normal); //1
make_vert(front_top_R, normal); //2
make_vert(front_top_L, normal); //3

//back
normal = glm::vec3(0.0, 0.0, 1.0);
make_vert(back_bot_L, normal); //4
make_vert(back_bot_R, normal); //5
make_vert(back_top_R, normal); //6
make_vert(back_top_L, normal); //7

//roof
normal = glm::vec3(0.0, 1.0, 0.0);
make_vert(front_top_L, normal); //8
make_vert(front_top_R, normal); //9
make_vert(back_top_L,  normal);  //10
make_vert(back_top_R,  normal);  //11

//floor
normal = glm::vec3(0.0, -1.0, 0.0);
make_vert(front_bot_L, normal); //12
make_vert(front_bot_R, normal); //13
make_vert(back_bot_L,  normal);  //14
make_vert(back_bot_R,  normal);  //15

//left
normal = glm::vec3(-1.0, 0.0, 0.0);
make_vert(front_bot_L, normal); //16
make_vert(front_top_L, normal); //17
make_vert(back_bot_L,  normal);  //18
make_vert(back_top_L,  normal);  //19

//right
normal = glm::vec3(1.0, 0.0, 0.0);
make_vert(front_bot_R, normal); //20
make_vert(front_top_R, normal); //21
make_vert(back_bot_R,  normal);  //22
make_vert(back_top_R,  normal);  //23

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

float radious = 1.0;
int NSlices = 72;
float height = 2.0;

float angle = glm::radians(360.0 / NSlices);

M2_vertices.resize( 2 + (4 * NSlices));
k = 0; //reset index k

make_vert2(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));	//bottom center
make_vert2(glm::vec3(0.0, height, 0.0), glm::vec3(0.0, 1.0, 0.0));	//top center

glm::vec3 vecPos;

// Vertices definitions
normal = glm::vec3(0.0, -1.0, 0.0);
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radious * glm::cos(angle * i), 0.0, radious * glm::sin(angle * i));
	make_vert2(vecPos, normal);
}

normal = glm::vec3(0.0, 1.0, 0.0);
for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radious * glm::cos(angle * i), height, radious * glm::sin(angle * i));
	make_vert2(vecPos, normal);
}

for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radious * glm::cos(angle * i), 0.0, radious * glm::sin(angle * i));
	make_vert2(vecPos);
}

for (int i = 0; i < NSlices; i++)
{
	vecPos = glm::vec3(radious * glm::cos(angle * i), height, radious * glm::sin(angle * i));
	make_vert2(vecPos);
}

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)

M2_indices.resize( 3 * (4 * NSlices) );

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
for (int i = 0; i < NSlices; i++)
{
	if (i == 0) {
		make_face2(first + NSlices, first, last);
	} else {
		int nxt = i + first;
		make_face2(nxt + NSlices, nxt-1, nxt);
	}
}

first += NSlices;
last  += NSlices;

//tris from roof and down
for (int i = 0; i < NSlices; i++)
{
	if (i == 0) {
		make_face2(last - NSlices, first, last);
	} else {
		int nxt = i + first;
		make_face2(nxt - NSlices -1, nxt-1, nxt);
	}
}







//// M3 : Sphere
// Replace the code below, that creates a simple triangle, with the one to create a sphere.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices

float rad = 1.0;
float hslice = 30.0;
float vslice = 20.0;
float hangle = (float)360.0 / hslice;
float vangle = (float)180.0 / vslice;

float x, y, z;

M3_vertices.resize((hslice * vslice) + 2);
k = 0; //reset index k

// Vertices definitions
make_vert3(0.0, rad, 0.0);	//0 toppole
make_vert3(0.0, -rad, 0.0);	//1 botpole

//horizontal
for (int i = 0; i < hslice; i++)
{
	for (int j = 0; j < vslice; j++)
	{
		update_xyz(rad, hangle * i, vangle * (1 + j), &x, &y, &z);
		make_vert3(x, y, z); 
	}
}

// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M3_indices.resize(3 * 2 * (hslice * vslice));

// indices definitions
k = 0; //reset index k

int toppole_index = 0;
int botpole_index = 1;

first = 2;
last = vslice + 1;
int count = 0;

//horizontal
for (int j = 0; j < hslice; j++) {
	//vertical
	for (int i = 0; i < vslice-1; i++) {
		int cur = first + i;
		int nxt = cur + 1;
		int target = cur + vslice;
		if (j >= hslice - 1) { //if on the last
			target = i + 2;
		}
		make_face3(target, cur, nxt); //add first tris for quad

		if (i == 0) {
			nxt = toppole_index; //add a top hat
		} else {
			nxt = target-1; //add a second tris for quad
		}
		make_face3(target, cur, nxt); 
	}
	first += vslice;
	last += vslice;
}




//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.


radious = 2.0;
NSlices = 72;
height = 10.0;
float irad = 0.2; //i = inner (cylinder along path)
int islice = 10;
float laps = 3.0;


angle = glm::radians(360.0 / NSlices);
float iangle = glm::radians(360.0 / islice);
int parts = NSlices * laps;
float zincrease = (height / (NSlices * islice));

M4_vertices.resize(parts * islice * 2);
k = 0; //reset index k

float icos, isin, currentRadious, zoffset;

for (int i = 0, k = 0; i < parts; i++)
{
	//spring cylinder along path
	for (int j = 0; j < islice; j++, k += 3)
	{
		icos = irad * glm::cos(iangle * j);
		isin = irad * glm::sin(iangle * j);
		currentRadious = radious + isin; //sine adapts radious
		zoffset = icos + (zincrease * i);  //cosine adapts height

		glm::vec3 cartesian, loopcenter;

		cartesian.x = currentRadious * glm::cos(angle * i);
		cartesian.y = zoffset;
		cartesian.z = currentRadious * glm::sin(angle * i);

		//Loopcenter calculation:
		loopcenter.x = radious * glm::cos(angle * i);
		loopcenter.y = zincrease * i;
		loopcenter.z = radious * glm::sin(angle * i);

		make_vert4(cartesian, loopcenter);
	}
}


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
int quads = parts * islice;
int tris = 2 * quads;
M4_indices.resize(2*3 * tris);
k = 0;

// indices definitions
int quadLoop = quads - islice;
for (int i = 0; i < quadLoop; i++)
{
	int source1 = i;
	int source2 = i + 1;
	int target1 = i + islice;
	int target2 = i + islice+1;
	make_face4(source1, source2, target1);

	//fix for when target should be index 0;
	if (i == quadLoop - 1) { //on last tris
		make_face4(0, islice-1, islice); 
	} else {
		make_face4(target1, target2, source2);
	}
}

}