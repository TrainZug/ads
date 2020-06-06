#include "sorting.h"
#include <algorithm>

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
			int q = (low + high) / 2;
			MergeSort(a, b, low, q);
			MergeSort(a, b, q + 1, high);
			Merge(a, b, low, q, high);
		}
	}

	void Merge (vector<int> & a, vector<int> & b, int left, int mid, int right) {
		for (int i = left; i <= right; i++) {
			b[i] = a[i];
		}
		int i = left;
		int l = left;
		int r = mid + 1;
		while (l <= mid && r <= right) {
			if (b[l] <= b[r]) {
				a[i++] = b[l++];
			} else {
				a[i++] = b[r++];
			}
		}
		while (l <= mid) {
			a[i++] = b[l++];
		}
		while (r <= right) {
			a[i++] = b[r++];
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
		for (int gap = n / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i += 1) {
				int temp = a[i];
				int j = i;
				for (; j >= gap && a[j - gap] > temp; j -= gap) {
					a[j] = a[j - gap];
				}
				a[j] = temp;
			}
		}
	}

	void randomizeVector (vector<int> & array, int n) {
		array.resize(n);
		for (unsigned int i = 0; i < array.size(); i++)
			array[i]        = rand() % 1000000;
	}

}