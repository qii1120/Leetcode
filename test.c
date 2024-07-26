#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <sys/time.h>

#include <pthread.h>
#define MAX 500

#define MAX_THREAD 4

void *function(void *arg)
{
	int i, j, row, col, k;
	int x = *((int *)arg);
	float val;
	double matrix1[MAX][MAX], matrix2[MAX][MAX], matrix3[MAX][MAX];
	char infilename[20], outfilename[20];
	FILE *infile, *outfile;
	infile = (FILE *)malloc(sizeof(FILE));
	outfile = (FILE *)malloc(sizeof(FILE));


	for (i = 0; i < MAX; i++)

		for (j = 0; j < MAX; j++)

			matrix1[i][j] = matrix2[i][j] = matrix3[i][j] = 0;

	sprintf(infilename, "in%d.txt", x % 3 + 1);

	sprintf(outfilename, "./folder/out%d.txt", x + 1);

	if ((infile = fopen(infilename, "r")) == NULL)
		perror("in open error~\n");

	fscanf(infile, "%d", &row);

	fscanf(infile, "%d", &col);

	printf("%d\n", x);

	for (i = 0; i < row; i++) // set matrix value

	{

		for (j = 0; j < col; j++)

		{

			fscanf(infile, "%f", &val);

			matrix1[i][j] = matrix2[i][j] = val;
		}
	}
	for (i = 0; i < row; i++) // matrix1's raw
	{
		for (j = 0; j < col; j++) // matrix2's col
		{
			val = 0;
			for (k = 0; k < row; k++) // matrix2's raw
			{
				val += (matrix1[i][k] * matrix2[k][j]);
			}
			matrix3[i][j] = val;
		}
	}

	if ((outfile = fopen(outfilename, "w")) == NULL)

		perror("out open error~\n");

	fprintf(outfile, "%d\n%d\n", row, col);

	for (i = 0; i < row; i++)

	{

		for (j = 0; j < col; j++)
		{
			fprintf(outfile, "%.0f\n", matrix3[i][j]);
		}
	}

	fclose(infile);

	fclose(outfile);
	free(infile);
	free(outfile);
	return NULL;
}

int main(void)

{
	struct timeval tp_s, tp_e;

	struct timezone tzp_s, tzp_e;
	FILE *timefile;
	pthread_t *threads;
	timefile = (FILE *)malloc(sizeof(FILE));

	threads = (pthread_t *)malloc(MAX_THREAD * sizeof(pthread_t));

	gettimeofday(&tp_s, &tzp_s);
	for (int i = 0; i < 1000; i+=4)
	{
		for (int j = 0; j < 4; j++)
		{
			int *p = (int *)malloc(sizeof(int));
			*p = (i + j);
			pthread_create(&threads[j], NULL, function, (void *)p);
		}
		// pthread_create(&threads[i % 4], NULL, function, (void *)p);
		for (int j = 0; j < 4; j++)
		{
			pthread_join(threads[j], NULL);
		}
	}
	gettimeofday(&tp_e, &tzp_e);

	if ((timefile = fopen("time.txt", "w")) == NULL)

		perror("out open error~\n");

	fprintf(timefile, "Total execution time =%ld\n", tp_e.tv_sec - tp_s.tv_sec);

	fclose(timefile);
	return 0;
}