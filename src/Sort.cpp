#include <iostream>
#include <algorithm>
#include <climits>
#include <time.h>
#include "Sort.h"

// ---------------------- SWAP ----------------
// Brief description: replace i and j elements
// --------------------------------------------
void swap(std::vector<int>& A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

// --------------------INSERTION SORT (p 48)---------------
// Brief description: sorting like in a gambling
// --------------------------------------------------------
// best = teta(n) 
// avg = teta(n^2)
// worst = teta(n^2) 
//---------------------------------------------------------
void Sort::insertionSort(std::vector<int>& A) {
	for (int j = 1; j < A.size(); j++) {
		int key = A[j];
		int i = j - 1;

		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

// --------------------SHELL SORT (S 258)--------------------------
// Brief description: insertion sort improvement using dynamic step
// ----------------------------------------------------------------
// worst = teta(n^(3 / 2)) 
//link: http://cybern.ru/sortirovka-shella-cpp.html
//-----------------------------------------------------------------
void Sort::ShellSort(std::vector<int>& A) {
	int step = A.size() / 2;
	while (step > 0) {
		for (int i = 0; i < A.size() - step; i++)
		{
			int j = i;
			while (j >= 0 && A[j] > A[j + step]) {
				swap(A, j, j + step);
				j--;
			}
		}
		step = step / 2; 
	}
}

// ---------------INSERTION SORT (RECURSIVE)--------
// Brief description: insertion sort using recursion 
// -------------------------------------------------
// best = teta(n) 
// avg = teta(n^2)
// worst = teta(n^2) 
//--------------------------------------------------
void Sort::insertionSortRecursive(std::vector<int>& A, int n) {
	if (n > 1)
		insertionSortRecursive(A, n - 1);
	
	int key = A[n];
	int i = n - 1;

	while (i >= 0 && A[i] > key) {
		A[i + 1] = A[i];
		i--;
	}
	A[i + 1] = key;
}

// --------------------BUBBLE SORT---------------------------
// Brief description: elements' pair replacement, 
// when minimal element goes to the beginning like a "bubble"
// ----------------------------------------------------------
// best = teta(n^2) 
// avg = teta(n^2)
// worst = teta(n^2) 
//---------------------------------------------------------
void Sort::bubbleSort(std::vector<int>& A) {
	for (int i = 0; i < A.size() - 1; i++) {
		bool swapped = false;

		for (int j = 0; j < A.size() - i - 1; j++) {
			if (A[j] > A[j + 1]) {
				swap(A, j, j + 1);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

//---------------------SELECTION SORT (p 52)------------------------
// Brief description: get minimum and put to 1st element.
// Put left elements, find min and place to the 2nd position and etc
//------------------------------------------------------------------
// best = teta(n^2)
// avg = teta(n^2)
// worst = teta(n^2)
//------------------------------------------------------------------ 
template <class Item>
void Sort::selectionSort(std::vector<Item>& A) {
	for (int i = 0; i < A.size() - 1; i++) {
		int minInd = i;
		
		for (int j = i + 1; j < A.size(); j++) {
			if (A[j] < A[minInd]) {
				minInd = j;
			}
		}
		swap(A, i, minInd);
	}
}

template void Sort::selectionSort<int>(std::vector<int>& A);

//--------ADDITIONAL FUNCTION FOR MERGE-SORT (p 54)--------
// Brief description: allows to join two sorted vectors to 
// one sorted vector 
//---------------------------------------------------------
// worst = teta(n)
//---------------------------------------------------------
void Sort::merge(std::vector<int>& A, int p, int q, int r) {

	const int lSize = q - p + 1;
	const int rSize = r - q;

	std::vector<int>::const_iterator begA = A.begin() + p;

	auto L = std::vector<int>(begA, begA + lSize);
	auto R = std::vector<int>(begA + lSize, begA + lSize + rSize);

	// signal card!
	L.push_back(INT_MAX);
	R.push_back(INT_MAX);

	int kl = 0;
	int kr = 0;

	// merge two arrays into one 
	for (int i = p; i <= r; i++) {
		if (L[kl] <= R[kr]) A[i] = L[kl++];
		else A[i] = R[kr++];
	}
}

//----------------------MERGE-SORT (p 56)--------------------
// Brief description: separate sequence parts recursievly and 
// merge sorted parts by merge() function
// ----------------------------------------------------------
// worst = teta(n * log(n) )
// ----------------------------------------------------------
void Sort::mergeSort(std::vector<int>& A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

//----------------------LEFT (p 180)--------------------
// Brief description: get left child of the current node
// -----------------------------------------------------
int Sort::left(int i) { return 2 * i; }

//----------------------RIGHT (p 180)--------------------
// Brief description: get right child of the current node
// -----------------------------------------------------
int Sort::right(int i) { return 2 * i + 1; }

//----------------------PARENT (p 180)----------------------
// Brief description: get parent node of the current child
// -------------------------------------------------------
int Sort::parent(int i) { return i / 2; }

//----------------------MAX-HEAPIFY (p 183)-----------------------------
// Brief description: get A-array, represent it as pyramid (binary tree),
// and transform it to non-increasing case for i-node and all its childs 
// ---------------------------------------------------------------------
// worst = teta(log(n) )
// ---------------------------------------------------------------------
void Sort::maxHeapify(std::vector<int>& A, int i, int heapSize) {
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < heapSize && A[i] < A[l]) largest = l;
	if (r < heapSize && A[largest] < A[r]) largest = r;

	if (largest != i) {
		swap(A, i, largest);
		maxHeapify(A, largest, heapSize);
	}
}

//----------------------MAX-HEAPIFY (p 185)-----------------------------
// Brief description: get A-array, represent it as pyramid (binary tree),
// and transform it to non-increasing pyramid 
// ---------------------------------------------------------------------
// worst = teta(n * log(n) )
// ---------------------------------------------------------------------
void Sort::buildMaxHeap(std::vector<int>& A) {
	for (int i = (A.size() - 1) / 2; i > 0; i--) {
		maxHeapify(A, i, A.size());
	}
}

//----------------------DUMMY-VECTOR-----------------
// Brief description: crutch to apply indexing from 1
// --------------------------------------------------
void dummyVector(std::vector<int>& A) {
	A.insert(A.begin(), -1);
}

//--------------UNDUMMY-VECTOR---------
// Brief description: remove crutch :) 
// ------------------------------------
void undummyVector(std::vector<int>& A) {
	A.erase(A.begin());
}

//------------------------------------HEAPSORT-----------------------------
// Brief description: get A-array, represent it as pyramid (binary tree),
// and transform it to non-increasing pyramid, using buildMaxHeap procedure.
// After that, extract the max pyramid element and put it to the end of tree,
// decrasing heap size.
// -------------------------------------------------------------------------
// worst = teta(n * log(n) )
// ---------------------------------------------------------------------
void Sort::heapSort(std::vector<int>& A) {
	dummyVector(A);

	int heapSize = A.size();
	buildMaxHeap(A);

	for (int i = A.size() - 1; i > 1; i--) {
		swap(A, 1, i);
		heapSize--;
		maxHeapify(A, 1, heapSize);
	}

	undummyVector(A);
}

//------------PARTITION (p 199)----------------
// Brief description: find reliable element q.
// --------------------------------------------
// avg = teta(n)
// --------------------------------------------
int Sort::partition(std::vector<int>& A, int p, int r) {
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap(A, i, j);
		}
	}
	swap(A, r, i + 1);

	return i + 1;
}

//----------------- PARTITION (p 207) ----------------
// Brief description: randomization helps to achieve 
// better perfomance for a quicksort
// ---------------------------------------------------
// avg = teta(n)
// ---------------------------------------------------
int Sort::randomizedPartition(std::vector<int>& A, int p, int r) {
	int i = rand() % (r - p + 1) + p;
	swap(A, i, r);

	return partition(A, p, r);
}

//----------------- PARTITION-GETTER -------------------------
// Brief description: get result from partition for Selection
// ----------------------------------------------------------
int getResultFromRandomizedPartition(std::vector<int>& A, int p, int r) {
	return Sort::randomizedPartition(A, p, r);
}

//---------------------- QUICKSORT (p 198)-----------------------------
// Brief description: use procedure "partition" to determine separation 
// element q. Next, use quicksort for 0 -> q, q + 1 -> p arrays. 
// ---------------------------------------------------------------------
// avg = teta(n * log(n) )
// worst = teta( n ^ 2 )
// ---------------------------------------------------------------------
void Sort::quickSort(std::vector<int>& A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

//---------------------- COUNTING-SORT (p 224)-----------------------------
// Brief description: plot a histogram C, find a number of less elements in 
// each cell, and put elements in B using information from C
// ---------------------------------------------------------------------
// avg = teta( n )
// ---------------------------------------------------------------------
void Sort::countingSort(std::vector<int>& A) {
	// find size of a histogram 
	std::vector<int>::iterator maxIter = std::max_element(A.begin(), A.end());
	std::vector<int> C((int) *maxIter + 1);
	
	// result vector 
	std::vector<int> B(A.size());

	// plot a histogram 
	for (int i = 0; i < A.size(); i++) C[A[i]]++;

	// find a number of less elements 
	for (int i = 1; i < C.size(); i++) C[i] += C[i - 1];

	for (int i = A.size(); i > 0; i--) {
		B[C[A[i - 1]] - 1] = A[i - 1];
		C[A[i - 1]]--;
	}
	A = B;
}

// ----------------- LAUNCHER ----------------------------
// Brief description: use all available sorting algorithms
// and compare their timings in console output 
// -------------------------------------------------------
void launchAllSortingAlgorithms() {
	//-------------------------------------------------
	std::vector<int> A;
	for (int i = 0; i < 1000; i++) A.push_back(rand());

	//-------------------------------------------------
	auto insStart = clock();
	auto ins = A;
	Sort::insertionSort(ins);
	auto insEnd = clock() - insStart;
	std::cout << "Insertion sort: " << insEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto insRStart = clock();
	auto insR = A;
	Sort::insertionSortRecursive(insR, insR.size() - 1);
	auto insREnd = clock() - insRStart;
	std::cout << "Insertion resursive sort: " << insREnd << " ms" << std::endl;

	//-------------------------------------------------
	auto selStart = clock();
	auto sel = A;
	Sort::selectionSort(sel);
	auto selEnd = clock() - selStart;
	std::cout << "Selection sort: " << selEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto merStart = clock();
	auto mer = A;
	Sort::mergeSort(mer, 0, mer.size() - 1);
	auto merEnd = clock() - merStart;
	std::cout << "Merge sort: " << merEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto bubStart = clock();
	auto bub = A;
	Sort::bubbleSort(bub);
	auto bubEnd = clock() - bubStart;
	std::cout << "Bubble sort: " << bubEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto pyrStart = clock();
	auto pyr = A;
	Sort::heapSort(pyr);
	auto pyrEnd = clock() - pyrStart;
	std::cout << "Heap sort: " << pyrEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto qStart = clock();
	auto qui = A;
	Sort::quickSort(qui, 0, qui.size() - 1);
	auto qEnd = clock() - qStart;
	std::cout << "Quick sort: " << qEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto countStart = clock();
	auto count = A;
	Sort::countingSort(count);
	auto countEnd = clock() - countStart;
	std::cout << "Counting sort: " << countEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto shStart = clock();
	auto sh = A;
	Sort::ShellSort(sh);
	auto shEnd = clock() - shStart;
	std::cout << "Shell sort: " << shEnd << " ms" << std::endl;

	//-------------------------------------------------
	bool check = (sel == ins) && 
				 (sel == mer) && 
				 (sel == bub) &&
				 (sel == pyr) &&
				 (sel == qui) &&
				 (sel == count) &&
				 (sel == sh) &&
				 (sel == insR);
	
	if (check) std::cout << "All sortings algorithms are correct" << std::endl << std::endl;
	else std::cout << "Error!" << std::endl << std::endl;
}