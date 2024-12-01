#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"
#include "mathutils.h"

// definition of global constatns

#include "globalconstants.h"

// definition of functions

int fillingSingleTransformationMatrix(float **t_matrix, int index, float **array);
int twoMatrixMultiplication(float **left_mx, int l_rows, int l_cols, float **right_mx, int r_rows, int r_cols);
void saveCoordinates(const char *filename, float x, float y, float z);
int getRegionIndex(float coord, float min, float max, int subdivisions);

int pointCalculation(float** array, int finish_flag, int region_counts[SUBDIV_X][SUBDIV_Y][SUBDIV_Z]) {
	const char *output_file = "coordinates.csv";
	int hit_flag = 0;
	int rows, cols;
	rows = LINKS;
	cols = DH_PARAMS_COLS;

	// 1. First step is filling transformation matrixes  
	// allocation space for T_matrixes
	float ***array_of_T_mx = malloc(LINKS * sizeof(float **));
	for (int i = 0; i < LINKS; i++) {
		// allocation space for i-links's transformation matrix
		array_of_T_mx[i] = malloc(TRANSFORM_MATRIX_DIM * sizeof(float *));
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			// allocation space for every i-mx j-row
			array_of_T_mx[i][j] = malloc(TRANSFORM_MATRIX_DIM * sizeof(float));
		}
		// filling i-link's trnsformation matrix !!!
		fillingSingleTransformationMatrix(array_of_T_mx[i], i, array);
	}
	// 2. Second step is multiplication of T-matrixes
	
	for (int mult_i = 1; mult_i < LINKS; mult_i++) {
		int tmd = TRANSFORM_MATRIX_DIM;
		twoMatrixMultiplication(array_of_T_mx[mult_i - 1], tmd, tmd, array_of_T_mx[mult_i], tmd, tmd);
	}

	// CHECKING HIT
	
	int x_region = getRegionIndex(array_of_T_mx[3][0][3], MIN_X, MAX_X, SUBDIV_X);
	int y_region = getRegionIndex(array_of_T_mx[3][1][3], MIN_Y, MAX_Y, SUBDIV_Y);
	int z_region = getRegionIndex(array_of_T_mx[3][2][3], MIN_Z, MAX_Z, SUBDIV_Z);

	if (x_region != -1 && y_region != -1 && z_region != -1) {
		region_counts[x_region][y_region][z_region]++;
		hit_flag = 1;
	}

	/*
	if (    (array_of_T_mx[3][0][3] >= MIN_X) && (array_of_T_mx[3][0][3] <= MAX_X) &&
		(array_of_T_mx[3][1][3] >= MIN_Y) && (array_of_T_mx[3][1][3] >= MAX_Y) &&
	       	(array_of_T_mx[3][2][3] >= MIN_Z) && (array_of_T_mx[3][2][3] >= MAX_Z)) {
		hit_flag = 1;
	}*/

	// SAVE FINAL RESULTS
	if (finish_flag) {
		saveCoordinates(output_file,  array_of_T_mx[3][0][3], array_of_T_mx[3][1][3], array_of_T_mx[3][2][3]);
		//printf("X Y Z: %f, %f, %f\n", array_of_T_mx[3][0][3], array_of_T_mx[3][1][3], array_of_T_mx[3][2][3]);
	}

	// memory deallocation
	for (int i = 0; i < LINKS; i++) {
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			free(array_of_T_mx[i][j]);
		}
		free(array_of_T_mx[i]);
	}
	free(array_of_T_mx);
       
	return hit_flag;
}

// functions

int fillingSingleTransformationMatrix(float **t_matrix, int index, float **array) {
	t_matrix[0][0] = cos(array[index][3]);
	t_matrix[0][1] = -sin(array[index][3]) * cos(array[index][1]);
	t_matrix[0][2] = sin(array[index][3])  * sin(array[index][1]);
	t_matrix[0][3] = array[index][0]       * cos(array[index][3]);
	
	t_matrix[1][0] = sin(array[index][3]);
	t_matrix[1][1] = cos(array[index][3])  * cos(array[index][1]);
	t_matrix[1][2] = -cos(array[index][3]) * sin(array[index][1]);
	t_matrix[1][3] = array[index][0]       * sin(array[index][3]);

	t_matrix[2][0] = 0;
	t_matrix[2][1] = sin(array[index][1]);
	t_matrix[2][2] = cos(array[index][1]);
	t_matrix[2][3] = array[index][2];

	t_matrix[3][0] = 0;
	t_matrix[3][1] = 0;
	t_matrix[3][2] = 0;
	t_matrix[3][3] = 1;

	return 0;
}

int twoMatrixMultiplication(float **left_mx, int l_rows, int l_cols, float **right_mx, int r_rows, int r_cols) {
	float **result = malloc(l_rows * sizeof(float *));
	for (int i = 0; i < l_rows; i++) {
		result[i] = malloc(r_cols * sizeof(float));
	}
	// MULTIPLICATION ITSELF
	
	for (int i = 0; i < l_rows; i++) {
		for (int j = 0; j < r_cols; j++) {
			result[i][j] = 0;
			for (int k = 0; k < l_cols; k++) {
				result[i][j] += left_mx[i][k] * right_mx[k][j];
			}
		}
	}

	// COPYPASTING TO RIGHT_MX

	for (int i = 0; i < l_rows; i++) {
		for (int j = 0; j < r_cols; j++) {
			right_mx[i][j] = result[i][j];
		}
	}

	//
	for (int i = 0; i < l_rows; i++) {
		free(result[i]);
	}
	free(result);

	return 0;
}

void saveCoordinates(const char *filename, float x, float y, float z) {
	FILE *file = fopen(filename, "a");
	fprintf(file, "%f, %f, %f\n", x, y, z);
	fclose(file);
}

int getRegionIndex(float coord, float min, float max, int subdivisions) {
	if (coord < min || coord > max) return -1;

	float step = (max - min) / subdivisions;
	return (int)((coord - min) / step);
}
