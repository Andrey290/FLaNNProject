#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "mathutils.h"

// definition of global constants

#include "globalconstants.h"

// definition of functions

int simulationFunction(float** array, int csv_flag, int region_counts[SUBDIV_X][SUBDIV_Y][SUBDIV_Z]) {
	int counter = 0; // counts hits
	float step  = CIRCLE / STEPS_NUMBER;

	for (int i_1 = 0; i_1 < STEPS_NUMBER; i_1++) {
		for (int i_2 = 0; i_2 < STEPS_NUMBER; i_2++) {
			for (int i_3 = 0; i_3 < STEPS_NUMBER; i_3++) {
				for (int i_4 = 0; i_4 < STEPS_NUMBER; i_4++) {
					array[3][3] = DEG_TO_RAD(i_4 * step);
					counter +=  pointCalculation(array, csv_flag, region_counts); // pointCalculation returns 1 if robot hits framefork
				}
				array[2][3] = DEG_TO_RAD(i_3 * step);
			}
			array[1][3] = DEG_TO_RAD(i_2 * step);
		}
		array[0][3] = DEG_TO_RAD(i_1 * step);
	}

	return counter;
}
