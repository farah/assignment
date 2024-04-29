/* An efficient search algorithm for 2D points:
 *
 * Skeleton code written by Jianzhong Qi, April 2024
 * Edited by: [Add your name and student ID here for automatic recognition]
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define STAGE_NUM_ONE 1 /* stage numbers */
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_HEADER "Stage %d\n==========\n" /* stage header format string */

#define DATA_SET_SIZE 50 /* number of input POIs */
#define DATA_DIM 2		 /* POI point dimensionality */
#define QUERY_SET_SIZE 5 /* number of input queries */
#define QUERY_BOUNDS 4	 /* query range bounds */

#define NUM_BITS 3 /* number of bits for col_/row_num */

#define BS_NOT_FOUND (-1) /* return status of binary search */
#define BS_FOUND 0
/****************************************************************/

/* function prototypes */
void print_stage_header(int stage_num);
void int_swap(int *p1, int *p2);
void sort_by_x(int ids[], double coordinates[][DATA_DIM], int num_pois);
int cal_curve_value(int col_num, int row_num);
int cmp(int *x1, int *x2);
int binary_search(int curve_values[], int lo, int hi,
				  int *key, int *locn);

void stage_one(int ids[], double coordinates[][DATA_DIM], int num_pois,
			   double queries[][QUERY_BOUNDS], int num_queries);
void stage_two(int ids[], double coordinates[][DATA_DIM], int num_pois,
			   double queries[][QUERY_BOUNDS], int num_queries);
void stage_three(int ids[], double coordinates[][DATA_DIM], int curve_values[],
				 int num_pois);
void stage_four(int ids[], double coordinates[][DATA_DIM], int curve_values[],
				int num_pois, double queries[][QUERY_BOUNDS], int num_queries);

int is_within_bounds(double point_x, double point_y,
					 double xlb, double ylb, double xub, double yub)
{
	return (point_x >= xlb && point_x <= xub) && (point_y >= ylb && point_y <= yub);
}

/* Function to print POIs within the first query */
void print_pois_in_query(int ids[], double coordinates[][DATA_DIM],
						 double query_bounds[QUERY_BOUNDS])
{
	int first_poi_printed = 0; // Flag to track the first printed POI

	for (int i = 0; i < DATA_SET_SIZE; i++)
	{
		if (is_within_bounds(coordinates[i][0], coordinates[i][1],
							 query_bounds[0], query_bounds[1],
							 query_bounds[2], query_bounds[3]))
		{
			if (first_poi_printed)
			{
				printf(" "); // Print a space before each subsequent POI ID
			}
			printf("%d", ids[i]);
			first_poi_printed = 1;
		}
	}

	if (!first_poi_printed)
	{
		printf(" none"); // Print "none" if no POIs are within the query bounds
	}
}

/* add your own function prototypes here */

/****************************************************************/

/* main function controls all the action */
int main(int argc, char *argv[])
{
	/* to hold all input data */
	int ids[DATA_SET_SIZE];
	double coordinates[DATA_SET_SIZE][DATA_DIM];
	double queries[QUERY_SET_SIZE][QUERY_BOUNDS];
	int curve_values[DATA_SET_SIZE];

	/* stage 1: read the input and answer the first query */
	stage_one(ids, coordinates, DATA_SET_SIZE, queries, QUERY_SET_SIZE);

	/* stage 2: sort and query POIs by the x-coordinates */
	stage_two(ids, coordinates, DATA_SET_SIZE, queries, QUERY_SET_SIZE);

	/* stage 3: calculate and sort by curve values */
	stage_three(ids, coordinates, curve_values, DATA_SET_SIZE);

	/* stage 4: query by curve values */
	stage_four(ids, coordinates, curve_values, DATA_SET_SIZE,
			   queries, QUERY_SET_SIZE);

	/* all done; take some rest */
	return 0;
}

/* print stage header given stage number */
void print_stage_header(int stage_num)
{
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* stage 1: read the input and answer the first query */
void stage_one(int ids[], double coordinates[][DATA_DIM], int num_pois,
			   double queries[][QUERY_BOUNDS], int num_queries)
{
	// Reading POI records: IDs and coordinates
	for (int i = 0; i < num_pois; i++)
	{
		if (scanf("%d %lf %lf;", &ids[i], &coordinates[i][0], &coordinates[i][1]) != 3)
		{
			fprintf(stderr, "Error reading the POI data.\n");
			exit(EXIT_FAILURE);
		}
		// Log the read POI for debugging purposes
		fprintf(stderr, "Read POI #%d: ID=%d, x=%lf, y=%lf\n",
				i, ids[i], coordinates[i][0], coordinates[i][1]);
	}

	// Reading the query ranges
	for (int i = 0; i < num_queries; i++)
	{
		if (scanf("%lf %lf %lf %lf", &queries[i][0], &queries[i][1], &queries[i][2], &queries[i][3]) != 4)
		{
			fprintf(stderr, "Error reading the query data.\n");
			exit(EXIT_FAILURE);
		}
		// Log the read query range for debugging purposes
		fprintf(stderr, "Read query #%d: xlb=%lf, ylb=%lf, xub=%lf, yub=%lf\n",
				i, queries[i][0], queries[i][1], queries[i][2], queries[i][3]);
	}
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);

	/* Call function to process and print POIs in the first query */
	printf("POIs in Q0:");
	print_pois_in_query(ids, coordinates, queries[0]);
	printf("\n"); // Move to a new line after printing all relevant POIs
}

/* stage 2: sort and query POIs by the x-coordinates */
void stage_two(int ids[], double coordinates[][DATA_DIM], int num_pois,
			   double queries[][QUERY_BOUNDS], int num_queries)
{
	/* add code for stage 2 */
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);

	sort_by_x(ids, coordinates, num_pois);
}

/* exchange the values of the two int variables indicated
	by the arguments, from
	https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/insertionsort.c */
void int_swap(int *p1, int *p2)
{
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/* insertion sort by x-coordinates, adapted from
   https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/insertionsort.c
*/
void sort_by_x(int ids[], double coordinates[][DATA_DIM], int num_pois)
{
	/* modify the code below to perform insertion sort to sort coordinates
		and ids by the x-coordinates
	*/
	/*
	int i, j;
	// assume that A[0] to A[n-1] have valid values
	for (i = 1; i < n; i++) {
		// swap A[i] left into correct position
		for (j= i-1; j >= 0 && A[j+1] < A[j]; j--) {
			// not there yet
			int_swap(&A[j], &A[j+1]);
		}
	}
	*/
}

/* stage 3: calculate and sort by curve values */
void stage_three(int ids[], double coordinates[][DATA_DIM], int curve_values[],
				 int num_pois)
{
	/* add code for stage 3 */
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
}

/* calculate the curve value given column number and row number
   DO NOT MODIFY THIS FUNCTION
*/
int cal_curve_value(int col_num, int row_num)
{
	int i, result = 0;

	for (i = NUM_BITS - 1; i >= 0; i--)
	{
		result += (row_num & (1 << i)) << (i + 1);
		result += (col_num & (1 << i)) << i;
	}

	return result;
}

/* comparison function used by binary search, adapted from
   https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/binarysearch.c
*/
int cmp(int *x1, int *x2)
{
	return (*x1 - *x2);
}

/* binary search over curve values, adapted from
   https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/binarysearch.c
*/
int binary_search(int curve_values[], int lo, int hi,
				  int *key, int *locn)
{
	/* modify the code below to perform binary search and find the smallest
		curve value greater than or equal to *key
	*/
	/*
	int mid, outcome;

	if (lo>=hi) {
		return BS_NOT_FOUND;
	}

	mid = (lo+hi)/2;
	if ((outcome = cmp(key, curve_values+mid)) < 0) {
		return binary_search(curve_values, lo, mid, key, locn);
	} else if (outcome > 0) {
		return binary_search(curve_values, mid+1, hi, key, locn);
	} else {
		*locn = mid;
		return BS_FOUND;
	}
	*/
	return BS_FOUND;
}

/* stage 4: query by curve values */
void stage_four(int ids[], double coordinates[][DATA_DIM], int curve_values[],
				int num_pois, double queries[][QUERY_BOUNDS], int num_queries)
{
	/* add code for stage 4 */
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
}