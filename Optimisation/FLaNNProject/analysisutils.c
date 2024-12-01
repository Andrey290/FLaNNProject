#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "simulation.h"
#include "mathutils.h"
#include "gradientdescent.h"
#include "fitness.h"

// definition of global constants

#include "globalconstants.h"

// definition of functions

float d(int index, float *lenghts) {
	switch (index) {
		case 0:
			return ((fitness(lenghts[0] + H, lenghts[1], lenghts[2], lenghts[3]) - fitness(lenghts[0] - H, lenghts[1], lenghts[2], lenghts[3])) / (2 * H));
		case 1:
			return ((fitness(lenghts[0], lenghts[1] + H, lenghts[2], lenghts[3]) - fitness(lenghts[0], lenghts[1] - H, lenghts[2], lenghts[3])) / (2 * H));
		case 2:
			return ((fitness(lenghts[0], lenghts[1], lenghts[2] + H, lenghts[3]) - fitness(lenghts[0], lenghts[1], lenghts[2] - H, lenghts[3])) / (2 * H));
		case 3:
			return ((fitness(lenghts[0], lenghts[1], lenghts[2], lenghts[3] + H) - fitness(lenghts[0], lenghts[1], lenghts[2], lenghts[3] - H)) / (2 * H));
	}
	return 0;
}
