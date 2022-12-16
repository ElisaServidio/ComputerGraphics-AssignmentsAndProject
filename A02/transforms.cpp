#include <cmath>

// Translate of +2 on the x axis, and -1 on the y axis
const float MT1[] = {
		   1.0,		0.0,		0.0,		2.0,
		   0.0,		1.0,		0.0,	   -1.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// Rotate of 45 degrees on the x axis 
/* Equations for the rotations among the x axis:
	x' = x
	y' = y ⋅ cosα − z ⋅ sinα
	z' = y ⋅ sinα + z ⋅ cosα
*/
const float MT2[] = {
		   1.0,		0.0,				0.0,				0.0,
		   0.0,		sqrt(2.0) / 2,	  		- sqrt(2.0) / 2,		0.0,
		   0.0,		sqrt(2.0) / 2,			sqrt(2.0) / 2,			0.0,
		   0.0,		0.0,				0.0,				1.0 };

// Make the object 2 times smaller
const float MT3[] = {
		   0.5,		0.0,		0.0,		0.0,
		   0.0,		0.5,		0.0,		0.0,
		   0.0,		0.0,		0.5,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// Make the object 2 times longer on the z axis, and half on the other axis
const float MT4[] = {
		   0.5,		0.0,		0.0,		0.0,
		   0.0,		0.5,		0.0,		0.0,
		   0.0,		0.0,		2.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// Mirror over the z axis. It can be obtained by using negative scaling factors
const float MT5[] = {
		  -1.0,		0.0,		0.0,		0.0,
		   0.0,	   -1.0,		0.0,		0.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// Flatten over the z axis. 
/*A scaling factor of 0 in any direction, flattens the image along that axis.
This however makes the transform matrix no longer invertible.
*/
const float MT6[] = {
		   1.0,		0.0,		0.0,		0.0,
		   0.0,		1.0,		0.0,		0.0,
		   0.0,		0.0,		0.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };

// Make a shear along the Y axis, with a factor of 1 along the x axis
/* Matrix formutation for the shear along the y axes:
				|1 hx 0 0|
				|0 1  0 0|
	Hy(hx, hz)= |0 hz 1 0|
				|0 0  0 1|
*/
const float MT7[] = {
		   1.0,		1.0,		0.0,		0.0,
		   0.0,		1.0,		0.0,		0.0,
		   0.0,		0.0,		1.0,		0.0,
		   0.0,		0.0,		0.0,		1.0 };
