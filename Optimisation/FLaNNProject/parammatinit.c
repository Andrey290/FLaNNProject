#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//definition of modules

#include "mathutils.h"

// definition of global constants

#include "globalconstants.h"

// definition of functions

int parametrs_filling(float **array, float L1, float L2, float L3, float L4,
		                     float O1, float O2, float O3, float O4) {
	array[0][0] = L1;
	array[1][0] = 0;
	array[2][0] = 0;
	array[3][0] = L4;

	array[0][1] = DEG_TO_RAD(-90);
	array[1][1] = DEG_TO_RAD(-90);
	array[2][1] = DEG_TO_RAD(90);
	array[3][1] = DEG_TO_RAD(90);

	array[0][2] = 0;
	array[1][2] = 0;
	array[2][2] = L3;
	array[3][2] = 0;

	array[0][3] = DEG_TO_RAD(O1);
	array[1][3] = DEG_TO_RAD(O2 - 90);
	array[2][3] = DEG_TO_RAD(O3);
	array[3][3] = DEG_TO_RAD(O4 + 90);
	
	return 0;
}
