#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include <omp.h>
#include "sorting.h"
#include "hashtable.h"

using namespace std;

//benchmark functions
void benchmark (string alg);

int main (int argc, char** argv) {

	Catch::Session().run();

	HashTable hashTable(1000);

	for (int i = 0; i < 200; i++) {
		hashTable.insert(rand() % (1500 - 1000 + 1) + 1000);
	}

	cout << "collisionCount: " << hashTable.getCollisionCount() << endl;

	std::cin.get();

	benchmark("Heapsort");
	benchmark("Mergesort");
	benchmark("Quicksort");
	benchmark("Shellsort");

	return 0;
}

//executes benchmark for quicksort
void benchmark (string alg) {
	cout << alg << " start" << endl;
	
	//file stream
	ofstream quicksort_measurement;
	quicksort_measurement.open(alg + ".txt", ios::out);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step  = 1000;
	int n_end   = 1000000;

	vector<int> V;
	vector<int> tmp;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		//std::cout << "Running " << alg << " with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//execzute sorting algorithm
		if (alg == "Quicksort") {
			//start measurement
			dtime = omp_get_wtime();
			sorting::QuickSort(V, 0, V.size() - 1);
			//stop time
			dtime = omp_get_wtime() - dtime;
		} else if (alg == "Heapsort") {
			//start measurement
			dtime = omp_get_wtime();
			sorting::HeapSort(V, V.size());
			//stop time
			dtime = omp_get_wtime() - dtime;
		} else if (alg == "Mergesort") {
			tmp.resize(V.size());
			//start measurement
			dtime = omp_get_wtime();
			sorting::MergeSort(V, tmp, 0, V.size() - 1);
			//stop time
			dtime = omp_get_wtime() - dtime;
		} else if (alg == "Shellsort") {
			//start measurement
			dtime = omp_get_wtime();
			sorting::ShellSort(V, V.size());
			//stop time
			dtime = omp_get_wtime() - dtime;
		}

		//write to file
		quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	quicksort_measurement.close();

	cout << alg << " fertig" << endl;
}
