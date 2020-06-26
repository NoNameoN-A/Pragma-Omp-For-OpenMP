#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

const int NUM_THREADS = 8;

int main() {
	////Esercizio 1
	const int matrix = 5000; 
	long double** a; 
	long double** b;
	a = new long double* [matrix];
	b = new long double* [matrix];
	for (int i = 0; i < matrix; i++) {
		a[i] = new long double[matrix];
		b[i] = new long double[matrix];
	}
	long double pgreco = 3.1415926535;
	long double startTime; 
	long double stopTime;
	const int num_threads = 8;
	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{
		if (omp_get_thread_num() == 0) startTime = omp_get_wtime(); //inizio 

		#pragma omp for
			for (int i = 0; i < matrix; i++) {
				for (int j = 0; j < matrix; j++) {
					a[i][j] = 15 * pow(i, 2) + 5 * pgreco * pow(j, 6);
				}
			}
		//barrier		
		
		#pragma omp for
			for (int i = 0; i < matrix; i++) {
				for (int j = 0; j < matrix; j++) {
					b[i][j] = (11 / 5) * a[i][j];
				}
			}
		//barrier
	
		stopTime = omp_get_wtime(); //fine
	}
	for (int i = 0; i < matrix; i++) {
		delete[] a[i];
		delete[] b[i];
	}
	delete[] a;
	delete[] b;

	cout << " tempo impiegato: " << (stopTime - startTime) * 1000 << " millisecondi." << endl;
}