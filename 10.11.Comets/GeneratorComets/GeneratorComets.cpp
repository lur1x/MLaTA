#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <random>

int main()
{
	std::ofstream inputFile("../Comets/INPUT.TXT");

	const int N = 2000;
	const int T = 2000;

	std::mt19937 rng(time(nullptr));
	//std::uniform_int_distribution<int> dist_N_T(1, 2000);
	std::uniform_int_distribution<int> dist_A_B(-100, 100);

	//const int N = dist_N_T(rng);
	//const int T = dist_N_T(rng);

	inputFile << N << " " << T << "\n";

	for (int i = 0; i < N; ++i)
	{
		int A = dist_A_B(rng);
		int B = dist_A_B(rng);
		inputFile << A << " " << B << std::endl;
	}

	inputFile.close();
	std::cout << "Файл INPUT.TXT успешно сгенерирован." << std::endl;
	return 0;

}

