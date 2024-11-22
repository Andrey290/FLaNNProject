#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// definition of modules

#include "dhtmatrixcalc.h"

// definition of global constatns

#define DH_PARAMS_COLS 4
#define TRANSFORM_MATRIX_DIM 4

// definition of functions

int fillingSingleTransformationMatrix(float **t_matrix, int index, float **array);
int twoMatrixMultiplication(float **left_mx, int l_rows, int l_cols, float **right_mx, int r_rows, int r_cols);

int pointCalculation(int links, float** array) {
	// 0. Dfining time
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	// 1. First step is filling DH parametrs
	int rows, cols;
	//	printf("Input number of links: ");
	//	scanf("%d", &links);
	rows = links;
	cols = DH_PARAMS_COLS;

	//	printf("links: %d, ", links);
	//	printf("rows: %d, ", rows);
	//	printf("cols: %d.\n", cols);
	
/*	
	printf("\nFilled array of DH parametrs: \n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%.2f ", array[i][j]);
		}
		printf("\n");
	}
*/	

	// 2. Second step is filling transformation matrixes  
	// allocation space for T_matrixes
	float ***array_of_T_mx = malloc(links * sizeof(float **));
	for (int i = 0; i < links; i++) {
		// allocation space for i-links's transformation matrix
		array_of_T_mx[i] = malloc(TRANSFORM_MATRIX_DIM * sizeof(float *));
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			// allocation space for every i-mx j-row
			array_of_T_mx[i][j] = malloc(TRANSFORM_MATRIX_DIM * sizeof(float));
		}
		// filling i-link's trnsformation matrix !!!
		fillingSingleTransformationMatrix(array_of_T_mx[i], i, array);
	}

	// Test-output of last T-matrix
/*	 printf("\nLast T-matrix output:\n");
	for (int i = 0; i < TRANSFORM_MATRIX_DIM; i++) {
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			printf("%.2f ", array_of_T_mx[links - 1][i][j]);
		}
		printf("\n");
	}
*/
	// 3. Third step is multiplication of T-matrixes
	
	for (int mult_i = 1; mult_i < links; mult_i++) {
		int tmd = TRANSFORM_MATRIX_DIM;
		twoMatrixMultiplication(array_of_T_mx[mult_i - 1], tmd, tmd, array_of_T_mx[mult_i], tmd, tmd);
	}
/*	
	printf("\nRESULT MATRIX (AFTER MULTIPLICATION):\n");
	for (int i = 0; i < TRANSFORM_MATRIX_DIM; i++) {
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			printf("%.2f ", array_of_T_mx[links - 1][i][j]);
		}
		printf("\n");
	}
*/
	// memory deallocation
	for (int i = 0; i < links; i++) {
		for (int j = 0; j < TRANSFORM_MATRIX_DIM; j++) {
			free(array_of_T_mx[i][j]);
		}
		free(array_of_T_mx[i]);
	}
	free(array_of_T_mx);
	// end
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("Time %.5f seconds\n", cpu_time_used);
       
	return 0;
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
