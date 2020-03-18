#include "Output.h"

Output::Output() {}
Output::~Output() { ofStream.close(); }
Output::Output(std::string name) 
{ 
	fileName = name; 
	ofStream.open(fileName);
}

void Output::writePPM(int* outputBuffer, const int& width, const int& height) 
{
	// Specification for png file
	ofStream << "P3\n" << width << " " << height << "\n255\n";

	// Fill image
	// Bottom to top
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			int r = outputBuffer[(y * width + x) * 3];
			int g = outputBuffer[(y * width + x) * 3 + 1];
			int b = outputBuffer[(y * width + x) * 3 + 2];
			ofStream << r << " " << g << " " << b << "\n";
		}
	}
}
void Output::close()
{
	ofStream.close();
}

std::string Output::getFileName() const { return fileName; }