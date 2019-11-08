#include <iostream>
#include <cstdio>


#define SIZE 128


int main()
{
	std::cout << "Hello world!" << std::endl;

	float *vec = (float *) _mm_malloc(SIZE * sizeof(float), 64);
	float *mat = (float *) _mm_malloc(SIZE * SIZE * sizeof(float), 64);
	float *res = (float *) _mm_malloc(SIZE * sizeof(float), 64);

	for (size_t i = 0; i < SIZE; i++)
	{
		vec[i] = i;
		res[i] = .0f;
		for (size_t j = 0; j < SIZE; j++)
		{
			mat[i * SIZE + j] = i * j;
		}
	}

	for (size_t k = 0; k < 1000000; k++)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			#pragma omp simd
			for (size_t j = 0; j < SIZE; j++)
			{
				res[i] += vec[j] * mat[i * SIZE + j];
			}
		}
	}

	return 0;
}
