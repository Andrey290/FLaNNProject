#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "mathutils.h"

// definition of global constants

#include "globalconstants.h"

// definition of functions

int simulationFunction(int number_of_steps,
		int links,
		float** array) {
	float step  = CIRCLE / number_of_steps;
	clock_t start, end;
	double total_cpu_time;
	start = clock();

	for (int i_1 = 0; i_1 < number_of_steps; i_1++) {
		for (int i_2 = 0; i_2 < number_of_steps; i_2++) {
			for (int i_3 = 0; i_3 < number_of_steps; i_3++) {
				for (int i_4 = 0; i_4 < number_of_steps; i_4++) {
					array[3][3] = DEG_TO_RAD(i_4 * step);
					pointCalculation(links, array);
				}
				array[2][3] = DEG_TO_RAD(i_3 * step);
			}
			array[1][3] = DEG_TO_RAD(i_2 * step);
		}
		array[0][3] = DEG_TO_RAD(i_1 * step);
	}

	end = clock();
	total_cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("||| Total simulation time is: %.5f seconds. |||", total_cpu_time);

	return 0;
}

