#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

#define STEPS_NUMBER 36
#define LINKS 4
#define DH_PARAMS_COLS 4
#define TRANSFORM_MATRIX_DIM 4
#define CIRCLE 360

    // gradient method //

#define H 0.0001           // dim step
#define EPSILON 0.0001     // stop condition
#define MAX_STEPS_COUNT 10 // second stop condition
#define ALPHA 0.2          // weight of links lenghts
#define BETA 0.4           // weight of inclusion
#define GAMMA 0.4          // homogeneity
   
    //  start lenghts  //

#define START_L1 3
#define START_L2 0
#define START_L3 5
#define START_L4 10

    // robots framework //
#define SUBDIV_X 10
#define SUBDIV_Z 10
#define SUBDIV_Y 10

#define MAX_X 10
#define MIN_X -10

#define MAX_Y 10
#define MIN_Y -10

#define MAX_Z 10
#define MIN_Z 0

#endif
