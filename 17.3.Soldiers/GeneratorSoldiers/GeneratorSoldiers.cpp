#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>


int main() {
    std::ofstream inputFile("../Soldiers/INPUT.TXT");
	std::random_device rd;
	std::mt19937 gen(rd());

	const int N = 200000;
    inputFile << N << "\n";

    std::vector<int> soldiers;

    std::uniform_int_distribution<> height_dist(1, 100000);

    std::uniform_real_distribution<> prob_dist(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        if (soldiers.empty() || prob_dist(gen) < 0.7) {
            
            int height = height_dist(gen);
            inputFile << "1 " << height << "\n";
            soldiers.push_back(height);
        }
        else {

            std::uniform_int_distribution<> pos_dist(1, soldiers.size());
            int pos = pos_dist(gen);
            inputFile << "2 " << pos << "\n";
            soldiers.erase(soldiers.begin() + pos - 1);
        }
    }

    inputFile.close();
	std::cout << "Файл INPUT.TXT успешно сгенерирован с " << N << " командами.\n";
    return 0;
}