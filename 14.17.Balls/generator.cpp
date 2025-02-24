#include <fstream>
#include <iostream>
#include <random>
#include <string>




std::string GenerateBallDirections(int length)
{
	std::string result;
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> dis(0, 1); 

	unsigned int rightCount = 0;
	unsigned int leftCount = 0;

	for (int i = 0; i < length; ++i)
	{
		if (dis(gen) == 0) // 0 -> '>', 1 -> '<'
		{
			result += '>';
			rightCount++;
		}
		else
		{
			result += '<';
			leftCount++;
		}
	}
	std::cout << "Generated data written to input.txt\n";
	std::cout << "Number of '>': " << rightCount << "\n";
	std::cout << "Number of '<': " << leftCount << "\n";

	return result;
}

int main()
{
	int length;
	std::cout << "Enter the number of balls (length of the string): ";
	std::cin >> length;

	if (length <= 0 || length > 1000000)
	{
		std::cerr << "Error: invalid number.\n";
		return 1;
	}

	std::string ballDirections = GenerateBallDirections(length);

	std::ofstream outputFile("input.txt");
	if (!outputFile.is_open())
	{
		std::cerr << "Error: Failed to open input.txt for writing.\n";
		return 1;
	}
	outputFile << ballDirections;
	outputFile.close();

	std::cout << "Generated data written to input.txt\n";
	return 0;
}