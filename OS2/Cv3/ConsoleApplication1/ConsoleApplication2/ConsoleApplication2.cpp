#include "pch.h"
#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;

int main(int argc, char* argv[])
{ 
	int time = atoi(argv[0]);
	int sleptTime = 0;

	cout << "Start" << endl;
	auto tStart = chrono::high_resolution_clock::now();
	while (sleptTime <= time) {
		auto end_time = std::chrono::high_resolution_clock::now();
		auto time = end_time - tStart;
		cout << "Time from start: " << time / chrono::milliseconds(1) << "ms" << endl;
		Sleep(100);
		sleptTime += 100;
	}
	cout << "End" << endl;
	return 0;
}

