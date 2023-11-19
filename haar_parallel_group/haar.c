#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define pixel(x,y) pixels[((y)*size)+(x)]

//#define DEBUG

void print(int *pixels, int size) {
	int x, y;
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			printf("%10d ", pixel(x,y));
		}
		printf("\n");
		fflush(stdout);
	}
}

int main(int argc, char *argv[]) {

	double itime, ftime, exec_time;
    itime = omp_get_wtime();

	FILE *in;
	FILE *out;

	in = fopen("image.in", "rb");
	if (in == NULL) {
		perror("image.in");
		exit(EXIT_FAILURE);
	}

	out = fopen("image.out", "wb");
	if (out == NULL) {
		perror("image.out");
		exit(EXIT_FAILURE);
	}

	long long int s, size, mid;
	int x, y;
	long long int a, d;
	double SQRT_2;

	fread(&size, sizeof(size), 1, in);

	fwrite(&size, sizeof(size), 1, out);

	int *pixels = (int *) malloc(size * size * sizeof(int));

	if (!fread(pixels, size * size * sizeof(int), 1, in)) {
		perror("read error");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	printf("origin: %lld\n", size);
	print(pixels, size);
#endif

	ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("Label: Pré-haar\n");
	printf("Elapsed Time: %f\n", exec_time);
	itime = omp_get_wtime();

	// haar
	SQRT_2 = sqrt(2);
	for (s = size; s > 1; s /= 2) {
		//start_time_internal = omp_get_wtime();
		
		mid = s / 2;
		// row-transformation
		#pragma omp parallel
		#pragma omp for nowait collapse(2)
		for (y = 0; y < mid; y++) {
			for (x = 0; x < mid; x++) {
				a = pixel(x,y);
				a = (a+pixel(mid+x,y))/SQRT_2;
				d = pixel(x,y);
				d = (d-pixel(mid+x,y))/SQRT_2;
				pixel(x,y) = a;
				pixel(mid+x,y) = d;
			}
		}	
#ifdef DEBUG
		printf("after row-transformation: %lld\n", mid);
		print(pixels, size);
#endif

		//start_time_internal = omp_get_wtime();
		// column-transformation
		#pragma omp parallel
		#pragma omp for nowait collapse(2)
		for (y = 0; y < mid; y++) {
			for (x = 0; x < mid; x++) {
				a = pixel(x,y);
				a = (a+pixel(x,mid+y))/SQRT_2;
				d = pixel(x,y);
				d = (d-pixel(x,mid+y))/SQRT_2;
				pixel(x,y) = a;
				pixel(x,mid+y) = d;
			}
		}

		// end_time_internal = omp_get_wtime();
    	// exec_time_internal = end_time_internal - start_time_internal;
    	// printf("[INTERNAL-%lld]Time taken is %f\n", s,exec_time_internal);

#ifdef DEBUG
		printf("after column-transformation: %lld\n", mid);
		print(pixels, size);
#endif
	}

	ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("Label1: Pós-haar\n");
	printf("Elapsed Time1: %f\n", exec_time);
	itime = omp_get_wtime();

	fwrite(pixels, size * size * sizeof(int), 1, out);

	free(pixels);

	fclose(out);
	fclose(in);

	ftime = omp_get_wtime();
	exec_time = ftime - itime;
    printf("Label2: Até-fim\n");
	printf("Elapsed Time2: %f\n", exec_time);

	return EXIT_SUCCESS;
}
