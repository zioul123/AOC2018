// Day22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable:4996)

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

int main()
{
	// Get input
	int d, tx, ty;
	scanf_s("depth: %d\n", &d);
	scanf_s("target: %d,%d\n", &tx, &ty);
	auto start = std::chrono::system_clock::now();
	time_t start_time = std::chrono::system_clock::to_time_t(start);

	cout << "Depth: " << d << ", Target: " << tx << "," << ty << ", start time: " << std::ctime(&start_time) << endl;

	// Initialize the map
	vector<vector<int>> geoIdx;
	vector<vector<int>> eroLvl;
	for (int i = 0; i <= ty; i++) {
		vector<int> v(tx + 1, 0);
		vector<int> e(tx + 1, 0);
		geoIdx.push_back(v);
		eroLvl.push_back(e);
	}
	auto curr = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = curr - start;
	cout << "Vectors initialized. Time: " << elapsed_seconds.count() << "s" << endl;

	// Initialize the map
	for (int i = 1; i <= tx; i++) {
		geoIdx[0][i] = (geoIdx[0][i - 1] + 16807) % 20183;
		eroLvl[0][i] = (geoIdx[0][i] + d) % 20183;
	}
	for (int i = 1; i <= ty; i++) {
		geoIdx[i][0] = (geoIdx[i - 1][0] + 48271) % 20183;
		eroLvl[i][0] = (geoIdx[i][0] + d) % 20183;
	}
	curr = std::chrono::system_clock::now();
	elapsed_seconds = curr - start;
	cout << "Initialized geoIdx." << "Time: " << elapsed_seconds.count() << "s" << endl;

	// Calculate geoIdx and erolvl
	for (int i = 1; i <= ty; i++) {
		for (int j = 1; j <= tx; j++) {
			geoIdx[i][j] = (eroLvl[i - 1][j] * eroLvl[i][j - 1]) % 20183;
			eroLvl[i][j] = (geoIdx[i][j] + d) % 20183;
		}
	}
	geoIdx[ty][tx] = 0;
	eroLvl[ty][tx] = 0;
	curr = std::chrono::system_clock::now();
	elapsed_seconds = curr - start;
	cout << "GeoIdx and EroLvl calculted. Time: " << elapsed_seconds.count() << "s" << endl;
	
	// Calculate risk
	int risk = 0;
	for (int i = 0; i <= ty; i++) {
		for (int j = 0; j <= tx; j++) {
			risk += eroLvl[i][j] % 3;
		}
	}
	curr = std::chrono::system_clock::now();
	elapsed_seconds = curr - start;
	cout << "Risk calculated. Time: " << elapsed_seconds.count() << "s" << endl;
	cout << ty << "," << tx << ", risk: " << risk << endl;
	return risk;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
