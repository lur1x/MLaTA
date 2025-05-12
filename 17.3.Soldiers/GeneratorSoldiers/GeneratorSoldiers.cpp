// Genarat#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ofstream inputFile("../Soldiers/INPUT.TXT");
    random_device rd;
    mt19937 gen(rd());

    // Количество команд (можно изменить)
	const int N = 200000;
    inputFile << N << "\n";

    // Вектор для хранения текущих солдат (для команд удаления)
    vector<int> soldiers;

    // Генератор случайных чисел для роста (от 1 до 100000)
    uniform_int_distribution<> height_dist(1, 100000);

    // Вероятность команды добавления (70%) или удаления (30%)
    uniform_real_distribution<> prob_dist(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        if (soldiers.empty() || prob_dist(gen) < 0.7) {
            // Команда добавления (1 X)
            int height = height_dist(gen);
            inputFile << "1 " << height << "\n";
            soldiers.push_back(height);
        }
        else {
            // Команда удаления (2 Y)
            uniform_int_distribution<> pos_dist(1, soldiers.size());
            int pos = pos_dist(gen);
            inputFile << "2 " << pos << "\n";
            soldiers.erase(soldiers.begin() + pos - 1);
        }
    }

    inputFile.close();
    cout << "Файл INPUT.TXT успешно сгенерирован с " << N << " командами.\n";
    return 0;
}