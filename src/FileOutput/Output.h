#pragma once
#include <fstream>
#include <string>

class Output
{
	private:
		std::string fileName;
		std::ofstream ofStream;

	public:
		Output();
		~Output();
		Output(std::string name);

		void writePPM(int* outputBuffer, const int& width, const int& height);
		void close();

		std::string getFileName() const;
};
