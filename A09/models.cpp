//functions to define the -ish vertex coordinates of each vertex of each model

void make_vert(int tmp, double x, double y, double z) {
	M1_vertices[tmp] = x;
	M1_vertices[tmp+1] = y;
	M1_vertices[tmp+2] = z;
}
void make_vert2(int tmp, double x, double y, double z) {
	M2_vertices[tmp] = x;
	M2_vertices[tmp + 1] = y;
	M2_vertices[tmp + 2] = z;
}
void make_vert3(int tmp, double x, double y, double z) {
	M3_vertices[tmp] = x;
	M3_vertices[tmp + 1] = y;
	M3_vertices[tmp + 2] = z;
}
void make_vert4(int tmp, double x, double y, double z) {
	M4_vertices[tmp] = x;
	M4_vertices[tmp + 1] = y;
	M4_vertices[tmp + 2] = z;
}

//functions to define models indices of triangles 
void make_face(int tmp, int v1, int v2, int v3) {
	M1_indices[tmp] = v1;
	M1_indices[tmp + 1] = v2;
	M1_indices[tmp + 2] = v3;
}
void make_face2(int tmp, int v1, int v2, int v3) {
	M2_indices[tmp] = v1;
	M2_indices[tmp + 1] = v2;
	M2_indices[tmp + 2] = v3;
}
void make_face3(int tmp, int v1, int v2, int v3) {
	M3_indices[tmp] = v1;
	M3_indices[tmp + 1] = v2;
	M3_indices[tmp + 2] = v3;
}
void make_face4(int tmp, int v1, int v2, int v3) {
	M4_indices[tmp] = v1;
	M4_indices[tmp + 1] = v2;
	M4_indices[tmp + 2] = v3;
}


//each face is made by two triangles, we recall the function make_face with 3 parameters as input to build those triangles
void make_face(int tmp, int v1, int v2, int v3, int v4) {
	make_face(tmp, v1, v2, v3);
	make_face(tmp+3, v4, v3, v1);
}
void make_face2(int tmp, int v1, int v2, int v3, int v4) {
	make_face2(tmp, v1, v2, v3);
	make_face2(tmp+3, v4, v3, v1);
}
void make_face3(int tmp, int v1, int v2, int v3, int v4) {
	make_face3(tmp, v1, v2, v3);
	make_face3(tmp + 3, v4, v3, v1);
}
void make_face4(int tmp, int v1, int v2, int v3, int v4) {
	make_face4(tmp, v1, v2, v3);
	make_face4(tmp + 3, v4, v3, v1);
}


//function called by the sphere model to updat the position of the vertex along the sphere circumference
void update_xyz(float r, float hang, float vang, float *x, float *y, float *z) {
	vang = glm::radians(vang);
	hang = glm::radians(hang);
	x[0] = r * cos(hang) * sin(vang);	// R * cosv * cosu
	z[0] = r * sin(hang) * sin(vang);	// R * sinv * cosu
	y[0] = r * cos(vang);				// R * cosu
}





// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels()
{
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M1_vertices.resize(3 * 8);

	make_vert(0, 0.0, 0.0, 0.0);		//0
	make_vert(3, 0.0, 0.0, 1.0);		//1
	make_vert(6, 0.0, 1.0, 1.0);		//2 hr
	make_vert(9, 0.0, 1.0, 0.0);		//3 hl

	make_vert(12, 1.0, 0.0, 0.0);		//4
	make_vert(15, 1.0, 0.0, 1.0);		//5
	make_vert(18, 1.0, 1.0, 1.0);		//6 hr
	make_vert(21, 1.0, 1.0, 0.0);		//7 hl

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 12);

	make_face(0, 0, 1, 2, 3);		//	front
	make_face(6, 4, 5, 6, 7);		//	back
	make_face(6 * 2, 2, 3, 7, 6);		//	roof
	make_face(6 * 3, 0, 1, 5, 4);		//	floor
	make_face(6 * 4, 1, 5, 6, 2);		//	left
	make_face(6 * 5, 0, 4, 7, 3);		//	right






	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	float radious = 1.0;
	int NSlices = 72;
	float height = 2.0;


	float angle = glm::radians(360.0 / NSlices);

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M2_vertices.resize((3 * (NSlices + 1)) * 2);

	// Vertices definitions

	//for loop to define vertices of lower circumference
	for (int i = 0, j = 0; i < NSlices + 1; i++, j += 3)
	{
		make_vert2(j, radious * glm::cos(angle * i), 0.0, radious * glm::sin(angle * i)); 
	}

	//for loop to define vertices of upper circumference
	for (int i2 = 0, j = 3 * (NSlices + 1); i2 < NSlices + 1; i2++, j += 3)
	{
		make_vert2(j, radious * glm::cos(angle * i2), height, radious * glm::sin(angle * i2)); 
	}

	make_vert2(0, 0.0, 0.0, 0.0);				//0 center of lower circumference
	make_vert2(3 * (NSlices + 1), 0.0, height, 0.0);	//0 center of upper circumference

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(5 * (3 * (NSlices + 1)));

	// indices definitions
	

	//floor
	for (int i = 1, k = 0; i < NSlices + 1; i++, k += 3)
	{
		if (i >= NSlices) {
			make_face2(k, 0, i, 1);
		}
		else {
			make_face2(k, 0, i, i + 1);
		}
	}

	//roof
	for (int i = 1, k = 3 * (NSlices + 1); i < NSlices + 1; i++, k += 3)
	{
		if (i >= NSlices)
		{
			make_face2(k, NSlices + 1, NSlices + 1 + i, NSlices + 2);
		}
		else {
			make_face2(k, NSlices + 1, NSlices + 1 + i, NSlices + 2 + i);
		}
	}

	//walls
	int tmp = 2 * (3 * (NSlices + 1));
	for (int i = 1, k = tmp; i < NSlices + 1; i++, k += 3) 
	{
		if (i >= NSlices)
		{
			make_face2(k, i, 1, NSlices + 1 + i);
			make_face2(k + tmp, NSlices + 2, 1, NSlices + 1 + i);
		} else {
			make_face2(k, i, i + 1, NSlices + 1 + i);
			make_face2(k + tmp, NSlices + 2 + i, i + 1, NSlices + 1 + i);
		}
	}







	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	float rad = 1.0;
	float hslice = 30.0;
	float vslice = 20.0;
	float hangle = (float)360.0 / hslice;
	float vangle = (float)180.0 / vslice;


	float x, y, z;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M3_vertices.resize((6 * hslice * vslice) + 12);

	// Vertices definitions

	make_vert3(0, 0.0, rad, 0.0);		//0 toppole
	make_vert3(3 * 1, 0.0, -rad, 0.0);	//1 botpole

	//horizontal
	for (int i = 0; i < hslice; i++)
	{
		for (int j = 0; j < vslice; j++)
		{
			update_xyz(rad, hangle * i, vangle * (1 + j), &x, &y, &z);
			make_vert3(3 * (i + 2 + (hslice * j)), x, y, z); 
		}
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize(2 * 6 * hslice * (vslice + 1));   

	// indices definitions

	int offset = 0;
	int offset2 = hslice;
	int offset3 = hslice * 2;
	int offs1 = 0;
	int offs2 = 0;
	for (int i = 0, k = 0; i < hslice; i++, k += 3)
		{
		if (i >= hslice - 1)
		{
			for (int j = 0; j < vslice-1; j++)
			{
				offs1 = hslice * j;
				offs2 = hslice * (1 + j);
				make_face3(hslice * 3 * (1 + j * 2) + k, offs1 + i + 2, offs2 + i + 2, offs2 + 2);
				make_face3(hslice * 3 * (2 + j * 2) + k, offs1 + i + 2, offs1 + 2, offs2 + 2);
			}
		} else {
			make_face3(0 + k, 0, offset + i + 2, offset + i + 3);

			for (int j = 0; j < vslice-1; j++)
			{
				offs1 = hslice * j;
				offs2 = hslice * (1 + j);
				make_face3(hslice * 3 * (1 + j * 2) + k, offs1 + i + 2, offs2 + i + 2, offs2 + i + 3);
				make_face3(hslice * 3 * (2 + j * 2) + k, offs1 + i + 2, offs1 + i + 3, offs2 + i + 3);
				if (j >= vslice - 1)
				{
					make_face3(hslice * 3 * (1 + j * 2) + k, 1, offs1 + i + 3, offs2 + i + 3);
				}
			}
		}  

	make_face3(5679, 0, 2, 31);
	}






	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.

	radious = 2.0;
	NSlices = 72;
	height = 10.0;
	float irad = 0.2;
	int islice = 10;
	float laps = 3.0;


	angle = glm::radians(360.0 / NSlices);
	float iangle = glm::radians(360.0 / islice);
	int parts = NSlices * laps;
	float zincrease = (height / (NSlices*islice));

	M4_vertices.resize(3 * parts * islice * 2);

	// Vertices definitions
	float icos, isin, currentRadious, zoffset;

	//main spring rotation radious builder
	for (int i = 0, k = 0; i < parts; i++)
	{
		//spring cylinder along path
		for (int j = 0; j < islice; j++, k += 3)
		{
			icos = irad * glm::cos(iangle * j);
			isin = irad * glm::sin(iangle * j);
			currentRadious = radious + isin; //sine adapts radious
			zoffset = icos + (zincrease * i);  //cosine adapts height

			float rx = currentRadious * glm::cos(angle * i);
			float ry = zoffset;
			float rz = currentRadious * glm::sin(angle * i);

			make_vert4(k, rx, ry, rz);
		}
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	int quads = parts * islice;
	int tris = 2 * quads;
	M4_indices.resize(3 * tris);

	// indices definitions
	for (int i = 0; i < ((quads)-islice); i++)
	{
		make_face4(i * 3, i, i + 1, i + islice);
		make_face4((i + quads) * 3, i + islice, i, i + islice - 1);
	}
}