#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "simulation.h"
#include "mathutils.h"
#include "parammatinit.h"

// definition of global constants

#include "globalconstants.h"

// definition of functions

int gradientdescent(float *links_lenghts) {
	
	clock_t start, end;
	double total_time;
	start = clock();
	
	/////////////////////////////////////////////
	// 1. First step is starting optimisation //
	// //////////////////////////////////////////
	
	printf("Optimisation is going ...\n");

	// memory allocation for gradient
	float gradient = malloc(LINKS * sizeof(float));
	float local_epsilon = 9999; // Do smth with that !!!
				    // LOCAL EPSILON depends on step, calculated in every iteration
	
	// optimisation
	int step_counter = 0;
	while ((step_counter <= MAX_STEPS_COUNT) && (local_epsilon > EPSILON)) {
		printf("Step number %d.\n", step_counter);
		local_epsilon = 0;

		for (int i = 0; i < LINKS; i++) {
			gradient[i] = d(i, links_lenghts);
			local_epsilon += gradient[i];
			printf("dF/dL_%d = %.2f \n", i + 1, gradient[i]);
		}
		
		// change link_lenghts !!!
		
		step_counter++;

		printf("Progrss: %.2f.\n", (float)(100 * step_counter / MAX_STEPS_COUNT));
		printf("--------------\n");
	}

	/////////////////////////////////
	// 2. Second step is conclusion //
	/////////////////////////////////
	
	int rows, cols;
	rows = LINKS;
	cols = DH_PARAMS_COLS;

	// memory allocation for DH parametrs	
	float **array = malloc(rows * sizeof(float *));
	for (int i = 0; i < rows; i++) {
		array[i] = malloc(cols * sizeof(float));
	}

	parametrs_filling(array, links_lenghts[0], links_lenghts[1], links_lenghts[2], links_lenghts[3],  0, 0, 0, 0);
	// Write final results into COORDINATES.CSV !!!
	//____________________________//
	//|PLACE FOR FINAL SIMULATION|//
	//|__________________________|//	
	// memory deallocation
	free(gradient);
	
	for (int i = 0; i < rows; i++) {
		free(array[i]);
	}
	free(array);

	end = clock();
	total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("||| TOTAL GRADIENT DESCENT TIME IS: %.5f SECONDS. AKA: %.5f MINUTES |||\n(WITH OUTPUTS AND MEMORY W/R).", total_time, total_time / 60);
	
	return 0;
}


