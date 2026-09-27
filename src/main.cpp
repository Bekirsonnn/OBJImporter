#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

#include "obj-importer.h"
#include "obj-structs.h"

struct Timer
{
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	Timer()
	{
		start = std::chrono::system_clock::now();
	}

	~Timer()
	{
		end = std::chrono::system_clock::now();

		std::chrono::system_clock::duration duration = end - start;

		auto micro_s = std::chrono::duration_cast<std::chrono::microseconds> (duration).count();

		std::cout << "Time (micro secs): " << micro_s << "\n";
	}
};

int main()
{
	std::ifstream input_file("253K-Sphere.obj");

	Timer LoadTime;

	OBJ myOBJ = LoadOBJ(input_file);

	input_file.close();
}