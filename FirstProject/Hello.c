#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	static int N = 0;
	static int SUM_LIN = 0;
	static int SUM_PARALL = 0;
	int arrayRandNum[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int* arrayParallel;
	printf("Enter number: ");
	scanf_s("%d", &N);

	//arrayRandNum = malloc(N * sizeof(int));
	arrayParallel = malloc(4 * sizeof(int));
	int shift = 0;

	srand(time(NULL));

	//int c = 0;
	/*for (int i = 0; i < N; i++)
	{
		arrayRandNum[i] = rand() % (100) + 1;
	}*/

	for (int i = 0; i < N; i++)
	{
		printf("%d\n", arrayRandNum[i]);
	}

	SUM_LIN = sumLin(arrayRandNum, N);
	printf("Sum paralel: %d", SUM_LIN);

	int increment = 0;
	int lock = 0;


#pragma omp parallel
	{
		printf("%i/%i\n", omp_get_thread_num(), omp_get_num_threads());
		int* incr = NULL;
		int operation = 0;
		while ( operation == 0) {
			if (lock == 0) {
				lock = 1;
				incr = arrayRandNum + increment;
				printf("%d\n", *(arrayRandNum + increment));
				increment += 4;
				lock = 0;


				int sum = 0;
				for (int i = 0; i < 4; i++)
				{
					sum += *incr;
					incr+=1;
				}
				arrayParallel[shift] = sum;
				shift += 1;
				operation = 1;
			}
		}
		
	}

	for (int i = 0; i < 4; i++)
	{
		SUM_PARALL += *arrayParallel;
		arrayParallel++;
	}

	printf("Sum paralel: %d", SUM_PARALL);
	return 0;
}

int sumLin(int* pointer, int N) {

	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += *pointer;
		pointer++;
	}
	return sum;
}
