#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "simulation.h"
#include "mathutils.h"

// definition of global constatns

#include "globalconstants.h"

// definition of functions

int init_DHParametrs(float **array, int rows, int cols, float L_1, float L_3, float L_4,
		                                        float O_1, float O_2, float O_3, float O_4);

int main(void) {
	// 1. First step is filling DH parametrs
	int steps_number = 36;
	int links, rows, cols;
	links = 4;
	rows = links;
	cols = DH_PARAMS_COLS;
	
	float **array = malloc(rows * sizeof(float *));
	for (int i = 0; i < rows; i++) {
		array[i] = malloc(cols * sizeof(float));
	}

	init_DHParametrs(array, rows, cols, 3, 5, 10, 0, 0, 0, 0);
	
	// 2. Second step is starting simulation
	
	// RECOMMENDATIONS //
	// Also need to get point from pointCalculation() function [do not need to get orietnation]
	// Also need to allocate array of such points
	// Define edges of working area
	// 	or another way
	// In each iteration count points that pass working area edges
	// Always control CPU time
	
	simulationFunction(steps_number, links, array);

	// memory deallocation
	for (int i = 0; i < rows; i++) {
		free(array[i]);
	}
	free(array);

	// end
	return 0;
}

// functions

int init_DHParametrs(float **array, int rows, int cols, float L_1, float L_3, float L_4,
		                                        float O_1, float O_2, float O_3, float O_4) {
	array[0][0] = L_1;
	array[1][0] = 0;
	array[2][0] = 0;
	array[3][0] = L_4;
	
	array[0][1] = DEG_TO_RAD(-90);
	array[1][1] = DEG_TO_RAD(-90);
	array[2][1] = DEG_TO_RAD(90);
	array[3][1] = DEG_TO_RAD(90);

	array[0][2] = 0;
	array[1][2] = 0;
	array[2][2] = L_3;
	array[3][2] = 0;

	array[0][3] = DEG_TO_RAD(O_1);
	array[1][3] = DEG_TO_RAD(O_2 - 90);
	array[2][3] = DEG_TO_RAD(O_3);
	array[3][3] = DEG_TO_RAD(O_4 + 90);

	return 0;
}
