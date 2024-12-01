#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "simulation.h"
#include "mathutils.h"
#include "gradientdescent.h"

// definition of global constatns

#include "globalconstants.h"

// definition of functions

int main(void) {
	float *links_lenghts = malloc(4 * sizeof(float));
	links_lenghts[0] = START_L1;
	links_lenghts[1] = START_L2;
	links_lenghts[2] = START_L3;
	links_lenghts[3] = START_L4;

	printf("Starts with links lenghts:\n
			L1 = %.2f,\n
			L2 = %.2f,\n
			L3 = %.2f,\n
			L4 = %.2f;\n," links_lenghts[0], links_lenghts[1], links_lenghts[2], links_lenghts[3]);

	// OPTIMISATION BY GRADIENT DESCENT //
	gradientdescent(links_lenghts);
	
	printf("OPTIMISATION SUCCESSFULLY FINISHED\n
			L1 = %.2f,\n
			L2 = %.2f,\n
			L3 = %.2f,\n
			L4 = %.2f;\n
			SEE VISUALISATION IN COORDINATES.CSV FILE", links_lenghts[0], links_lenghts[1], links_lenghts[2], links_lenghts[3]);
	free(links_lenghts);
	
	return 0;
}
