#include "sorting.h"
#include <algorithm>
#include <cmath>

using namespace std;

namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort (vector<int> & arr, int left, int right) {
		if (left < right) {
			int pi = partition(arr, left, right);
			QuickSort(arr, left, pi - 1);
			QuickSort(arr, pi + 1, right);
		}
	}

	int partition (vector<int> & arr, int left, int right) {
		int pivot = arr[right];
		int i     = (left - 1);
		for (int j = left; j <= right - 1; j++) {
			if (arr[j] <= pivot) {
				swap(arr[++i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[right]);
		return (i + 1);
	}

	//************
	// MergeSort *
	//************
	void MergeSort (vector<int> & a, vector<int> & b, int low, int high) {
		if (low < high) {
			int center = (low + high) / 2;
			MergeSort(a, b, low, center);
			MergeSort(a, b, center + 1, high);
			Merge(a, b, low, center + 1, high);
		}
	}

	void Merge (vector<int> & a, vector<int> & b, int left, int mid, int right) {
		int leftEnd     = mid - 1;
		int tmpPos      = left;
		int numElements = right - left + 1;

		while (left <= leftEnd && mid <= right) {
			if (a[left] <= a[mid]) {
				b[tmpPos++] = a[left++];
			} else {
				b[tmpPos++] = a[mid++];
			}
		}
		while (left <= leftEnd) {
			b[tmpPos++] = a[left++];
		}
		while (mid <= right) {
			b[tmpPos++] = a[mid++];
		}
		for (int i = 0; i < numElements; i++, right--) {
			a[right] = b[right];
		}
	}

	//************
	// Heapsort  *
	//************
	void HeapSort (vector<int> & a, int n) {
		int i = n * 0.5;
		while (i >= 0) {
			percDown(a, i, n);
			i--;
		}
		int j = n - 1;
		while (j > 0) {
			swap(a[0], a[j]);
			percDown(a, 0, j);
			j--;
		}
	}

	inline int leftChild (int i) {
		return 2 * i + 1;
	}

	void percDown (vector<int> & A, int p, int n) {
		int child     = p;
		const int tmp = A[p];
		int j         = p;
		while (leftChild(j) < n) {
			child = leftChild(j);
			if ((child != (n - 1)) && (A[child] < A[child + 1])) {
				child++;
			}
			if (tmp < A[child]) {
				swap(A[j], A[child]);
				j = child;
			} else {
				return;
			}
		}
	}

	//************
	// Shellsort *
	//************
	void ShellSort (vector<int> & a, int n) {
		int k = log2(n) - 1;
		for (int gap = pow(2, k) - 1; gap > 0; gap = pow(2, --k) - 1) {
			for (int i = gap; i < n; i++) {
				int tmp = a[i];
				int j   = i;
				for (; j >= gap && tmp < a[j - gap]; j -= gap) {
					a[j] = a[j - gap];
				}
				a[j] = tmp;
			}
		}

	}

	void randomizeVector (vector<int> & array, int n) {
		array.resize(n);
		for (unsigned int i = 0; i < array.size(); i++) {
			array[i] = rand() % 1000000;
		}
	}

}
