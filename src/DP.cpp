#include <iostream>
#include <time.h>
#include <algorithm>
#include "DP.h"

//---------------------- CUT-ROD (p 396) -----------------------------------
// Brief description: we have a vector with price of rod part after cutting.
// Vector index means the length of the rod part. The main goal is 
// to maximize total price for sell.
// -------------------------------------------------------------------------
// Input : 
// Length (i)   | 1 | 2 | 3 | ... | n
// Price  (p_i) | 1 | 5 | 8 | ... | p_n
// -------------------------------------------------------------------------
int DP::cutRod(std::vector<int> p, int n) {
	if (n == 0) return 0;
	
	int q = -1;
	for (int i = 1; i <= n; i++) {
		q = std::max(q, p[i] + cutRod(p, n - i));
	}
	
	return q;
}

//---------------------MEMOIZED-CUT-ROD-AUX (WRAPPER) ------------------------
// Brief description: wrapper for memoizedCutRodAux() function
// ---------------------------------------------------------------------------
int DP::memoizedCutRod(std::vector<int> p, int n) {
	std::vector<int> r(n + 1, -1);
	return memoizedCutRodAux(p, r, n);
}

//---------------------- MEMOIZED-CUT-ROD-AUX (p 396) ------------------------
// Brief description: the same as a previoius task, but now we use DP to store
// tree values in additional arrat to avoid multiple recomputatation.
// ---------------------------------------------------------------------------
int DP::memoizedCutRodAux(std::vector<int> p, std::vector<int> r, int n) {
	// check if the cutRod for n was computed 
	if (r[n] >= 0) return r[n];
	
	int q;
	if (n == 0) q = 0; // crutch for convinient writing to "r"
	else {
		q == -1;
		for (int i = 1; i <= n; i++) {
			q = std::max(q, p[i] + memoizedCutRodAux(p, r, n - i));
		}
	}

	// write computed value 
	r[n] = q;

	return q;
}

//---------------------- BOTTOM-UP-CUT-ROD (p 399) ----------------------------
// Brief description: one more effective DP algorithm with another technique 
// of calculated elements storage 
// ---------------------------------------------------------------------------
int DP::bottomUpCutRod(std::vector<int> p, int n) {
	std::vector<int> r(n + 1, -1);
	r[0] = 0;

	for (int j = 1; j <= n; j++) {
		int q = -1;

		for (int i = 1; i <= j; i++) {
			q = std::max(q, p[i] + r[j - i]);
		}
		r[j] = q;
	}
	return r[n];
}

//---------------------- LCS-LENGTH (p 428)---------------------------------
// Brief description: main goal is to find the longest common subsequence of 
// two sequences.
// -------------------------------------------------------------------------
// Input : X = 1 2 0 2 1, Y = 1 3 0 2 1, Result = 1 0 2
// avg = O( m * n )
// -------------------------------------------------------------------------
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> DP::LCSlength(std::vector<int>& X, std::vector<int>& Y) {
	const int m = X.size();
	const int n = Y.size();
	
	std::vector<int> cN(n + 1, 0);
	std::vector<std::vector<int>> c(m + 1, cN);

	std::vector<int> bN(n + 1, 0);
	std::vector<std::vector<int>> b(m + 1, bN);
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (X[i] == Y[j]) {
				c[i + 1][j + 1] = c[i][j] + 1;
				b[i + 1][j + 1] = -1; // /
			}
			else if (c[i][j + 1] >= c[i + 1][j]) {
				c[i + 1][j + 1] = c[i][j + 1];
				b[i + 1][j + 1] = -2; // |
			}
			else {
				c[i+1][j+1] = c[i+1][j];
				b[i+1][j+1] = -3; // -
			}
		}
	}
	return std::make_pair(c, b);
}

//---------------------- PRINT-LCS (p 429)--------------
// Brief description: recursively print all LCS 
// -----------------------------------------------------
// avg = O( m + n )
// -----------------------------------------------------
void printLCS(std::vector<std::vector<int>> b, std::vector<int> X, int i, int j) {
	if (i == 0 || j == 0) return;
	if (b[i][j] == -1) {
		printLCS(b, X, i - 1, j - 1);
		std::cout << X[i - 1] << " ";
	}
	else if (b[i][j] == -2) {
		printLCS(b, X, i - 1, j);
	}
	else if (b[i][j] == -3) printLCS(b, X, i, j - 1);
}

//---------------------- FIBONACCI-ITERATIVE (S 202)-----------
// Brief description: find Fibonacci seq using iteration method
// ------------------------------------------------------------
// avg = O( n )
// -----------------------------------------------------
int DP::findFibonacciIter(int N) {
	std::vector<int> result = {0, 1};
	for (int i = 2; i <= N; i++) {
		result.push_back(result[i - 1] + result[i - 2]);
	}
	return result[result.size() - 1];
}

//---------------------- FIBONACCI-RECURSIVE (S 202)-----------
// Brief description: find Fibonacci seq using recursive method
// ------------------------------------------------------------
// avg = O( exp(n) )
// -----------------------------------------------------
int DP::findFibonacciRec(int N) {
	if (N < 1) return 0;
	if (N == 1) return 1;
	return DP::findFibonacciRec(N - 1) + DP::findFibonacciRec(N - 2);
}

//---------------------- FIBONACCI-TOP-DOWN (S 203)--------------
// Brief description: find Fibonacci seq using top-down DP method
// --------------------------------------------------------------
// avg = O( n )
// --------------------------------------------------------------
int DP::findFibonacciTopDown(int N) {
	static std::vector<int> knownN = { 0, 1 };
	if (N < knownN.size()) return knownN[N];
	
	knownN.push_back(DP::findFibonacciTopDown(N - 1) + DP::findFibonacciTopDown(N - 2));
	return knownN[knownN.size() - 1];
}


//---------------------- KNAP (S 204)--------------------------------
// Brief description: we have N kinds of things with different 
// weights and wealth. W - capacity of our knap. Need to find things
// combination to put in knap to maximize wealth.
// ------------------------------------------------------------------
// avg = O( exp( n ) )
// link: http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
// --------------------------------------------------------------
std::vector<DP::Item> DP::items = { { 3, 4 },{ 4,5 },{ 7,10 },{ 8,11 },{ 9, 13 } };
int DP::knap(int W, int n) {
	// Base Case
	if (n == 0 || W == 0)
		return 0;

	// If weight of the nth item is more than Knapsack capacity W, then
	// this item cannot be included in the optimal solution
	if (items[n - 1].size > W)
		return knap(W, n - 1);

	// Return the maximum of two cases: 
	// (1) nth item included 
	// (2) not included
	else return std::max(items[n - 1].val + knap(W - items[n - 1].size, n - 1),
		knap(W, n - 1)
	);
}

//---------------------- KNAP - DP --------------------------------
// Brief description: we have N kinds of things with different 
// weights and wealth. W - capacity of our knap. Need to find things
// combination to put in knap to maximize wealth.
// ------------------------------------------------------------------
// link: http://www.programminglogic.com/knapsack-problem-dynamic-programming-algorithm/
// --------------------------------------------------------------
int DP::knapDP(int W, int n) {
	static std::vector<std::vector<int>> known(1000, std::vector<int>(1000, 0));
	
	if (known[W][n] != 0)
		return known[W][n];

	// Base Case
	if (n == 0 || W == 0)
		return 0;

	// If weight of the nth item is more than Knapsack capacity W, then
	// this item cannot be included in the optimal solution
	if (items[n - 1].size > W)
		return knap(W, n - 1);

	// Return the maximum of two cases: 
	// (1) nth item included 
	// (2) not included
	else {
		int take = items[n - 1].val + knap(W - items[n - 1].size, n - 1);
		int donTake = knap(W, n - 1);
		known[W][n] = std::max(take, donTake);
		return known[W][n];
	}
}

// ----------------- LAUNCHER ----------------------------
// Brief description: use all available dynamic programming 
// algorithms and compare their timings in console output 
// -------------------------------------------------------
void launchDPAlgorithms() {
	//-------------------------------------------------
	std::vector<int> A;
	for (int i = 0; i < 10; i++) A.push_back(rand());

	//-------------------------------------------------
	auto crStart = clock();
	auto cr = A;
	int crResult = DP::cutRod(A, A.size() - 1);
	auto crEnd = clock() - crStart;
	std::cout << "Cut-Rod DP procedure: " << crEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto crmStart = clock();
	auto crm = A;
	int crmResult = DP::memoizedCutRod(A, A.size() - 1);
	auto crmEnd = clock() - crmStart;
	std::cout << "Memoized Cut-Rod DP procedure: " << crmEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto bucrStart = clock();
	auto bucr = A;
	int bucrResult = DP::bottomUpCutRod(A, A.size() - 1);
	auto bucrEnd = clock() - bucrStart;
	std::cout << "Bottom-up Cut-Rod DP procedure: " << bucrEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto lcsStart = clock();
	std::vector<int> Y = { 1, 3, 2, 0, 1, 0};
	std::vector<int> X = { 0, 1, 2, 1, 3, 0, 1 };
	auto lcsResult = DP::LCSlength(X, Y);
	std::cout << "algorithm result: ";
	printLCS(lcsResult.second, X, X.size(), Y.size());
	std::cout << std::endl << "GT result: " << "1 2 1 0" << std::endl;
	auto lcsEnd = clock() - lcsStart;
	std::cout << "LCS-length DP procedure: " << lcsEnd << " ms" << std::endl;

	//-------------------------------------------------
	const int fibInput = 30;
	auto fiStart = clock();
	auto fiResult = DP::findFibonacciIter(fibInput);
	auto fiEnd = clock() - fiStart;
	std::cout << "Fibonacci iteration: " << fiEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto fiRecStart = clock();
	auto fiRecResult = DP::findFibonacciRec(fibInput);
	auto fiRecEnd = clock() - fiRecStart;
	std::cout << "Fibonacci recursive: " << fiRecEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto fiDPStart = clock();
	auto fiDPResult = DP::findFibonacciTopDown(fibInput);
	auto fiDPEnd = clock() - fiDPStart;
	std::cout << "Fibonacci top-down DP method: " << fiDPEnd << " ms" << std::endl;

	//-------------------------------------------------
	const int knapSize = 17;
	auto knStart = clock();
	auto knResult = 0;
	for (int i = 0; i < 10; i++) knResult = DP::knap(knapSize, DP::items.size());
	auto knEnd = clock() - knStart;
	std::cout << "Knap task resursion method: " << knEnd << " ms" << std::endl;

	//-------------------------------------------------
	auto knDPStart = clock();
	auto knDPResult = 0;
	for (int i = 0; i < 10; i++) knDPResult = DP::knapDP(knapSize, DP::items.size());
	auto knDPEnd = clock() - knDPStart;
	std::cout << "Knap task resursion DP method: " << knDPEnd << " ms" << std::endl;

	//-------------------------------------------------
	bool check = (crResult == crmResult) &&
			     (crResult == bucrResult) && 
				 (fiRecResult == fiResult) &&
				 (fiDPResult == fiResult) && 
				 (knResult == knDPResult);

	if (check) std::cout << "All DP algorithms are correct" << std::endl << std::endl;
	else std::cout << "Error!" << std::endl << std::endl;
}