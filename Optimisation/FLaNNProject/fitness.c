#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "mathutils.h"
#include "analysis.h"
#include "simulation.h"
#include "dhtmatrixcalc.h"
#include "parammatinit.h"

// definition of global constants

#include "globalconstants.h"

//definition of function

float calculateUniformity(int region_counts[SUBDIV_X][SUBDIV_Y][SUBDIV_Z], int total_points);
float calculateUmax(int total_points);

float fitness(float L1, float L2, float L3, float L4) {
	int region_counts[SUBDIV_X][SUBDIV_Y][SUBDIV_Z] = {0};
	int rows, cols;
	rows = LINKS;
	cols = DH_PARAMS_COLS;
	
	// momory allocation for DH parametrs
	float **array = malloc(rows * sizeof(float *));
	for (int i = 0; i < rows; i++) {
		array[i] = malloc(cols * sizeof(float));
	}
	
	parametrs_filling(array, L1, L2, L3, L4, 0, 0, 0, 0);
	
	int   N             = simulationFunction(array, 0, region_counts);     // current number of points
	float U             = calculateUniformity(region_counts, N);           // current uniformity
	float Umax          = calculateUmax(N);                                // max uniformity
	float max_links_len = START_L1 + START_L2 + START_L3 + START_L4;       // max links len
	int   Nmax          = pow(STEPS_NUMBER, LINKS);                        // max number of points
	
	for (int i = 0; i < rows; i++) {
		free(array[i]);
	}
	free(array);

	return  ALPHA((L1 + L2 + L3 + L4) / max_links_len) +
	       	BETA(1 - ((float)N / (float)Nmax)) +
	       	GAMMA(1 - (U / Umax));
}


float calculateUniformity(int region_counts[SUBDIV_X][SUBDIV_Y][SUBDIV_Z], int total_points) {
	if (total_points == 0) {
		return 0.0;
	}

	// points in one cell in ideal case
	float expected_points = (float)total_points / (SUBDIV_X * SUBDIV_Y * SUBDIV_Z);
	float uniformity = 0.0;

	// summarizing sqrt deviation from expected value
	float deviation;
	for (int x = 0; x < SUBDIV_X; x++) {
		for (int y = 0; y < SUBDIV_Y; y++) {
			for (int z = 0; z < SUBDIV_Z; z++) {
				deviation = region_counts[x][y][z] - expected_points;
			        uniformity += deviation * deviation;
			}
		}
	}	
	
	// normalizing metrix
	uniformity = sqrt(uniformity / (SUBDIV_X * SUBDIV_Y * SUBDIV_Z));

	return 1.0 / (1.0 + uniformity);
}

float calculateUmax(int total_points) {
	int M = SUBDIV_X * SUBDIV_Y * SUBDIV_Z;

	float N_ideal = (float)total_points / M;

	float U_max = sqrt(
			(((total_points - N_ideal) * (total_points - N_ideal)) +
		        ((M - 1) * (0 - N_ideal) * (0 - N_ideal))) / M
			);
	return U_max;
}
