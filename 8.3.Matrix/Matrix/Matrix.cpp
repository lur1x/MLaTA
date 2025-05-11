/*
*
8.3. Матрица (8)
В матрице A размера N×N числа от 1 до N2. Каждое число записано ровно один раз. Даны две матрицы
размера N × N: Top и Left. Значение Topi j определяет количество чисел, больших Ai j и
расположенных выше по столбцу, Lefti j - количество чисел, больших Ai j и расположенных левее по
строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Ввод из файла INPUT.TXT. В первой строке N (1 ≤ N ≤100), затем N строк матрицы Top (числа через
пробел), затем N строк матрицы Left. Числа в обеих матрицах от 0 до N.
Вывод в файл OUTPUT.TXT матрицы A – N строк, числа в строке через пробел. Если решений нет,
вывести 0.


Пример:

Ввод
3
0 0 0
0 0 0
0 0 2
0 0 0
0 1 0
0 1 2

Вывод
1 2 6
5 3 7
9 8 4


Подсказка. Основной принцип – проставлять очередное число в цикле от 1 до N2 в такую клетку
(i, j), где i –номер строки, а  j – номер столбца, значение которой должно быть наименьшим
среди незаполненных клеток строки i и столбца j. Это свойство нужно уметь проверять по  матрицам
Top и Left. Тогда заполненная матрица не будет противоречить заданным условиям. Различных решений
может быть много.

ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using  Matrix = std::vector<std::vector<int>>;

void ReadMatrix(Matrix& matrix, const int N, std::ifstream& input)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			input >> matrix[i][j];
		}
	}
}

void PrintMatrix(Matrix& matrix, const int N, std::ofstream& output)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			output << matrix[i][j];
			if (j != N - 1)
			{
				output << " ";
			}
		}
		output << std::endl;
	}
}

int main() 
{
    std::ifstream inputFile("INPUT.TXT");
	std::ofstream outputFile("OUTPUT.TXT");

	auto start = std::chrono::high_resolution_clock::now();

    int N;
	inputFile >> N;

    Matrix top(N, std::vector<int>(N));
	ReadMatrix(top, N, inputFile);

    Matrix left(N, std::vector<int>(N));
	ReadMatrix(left, N, inputFile);

    Matrix A(N, std::vector<int>(N, 0));

    for (int k = N * N; k >= 1; --k)
	{
		bool found = false;
		for (int i = N - 1; i >= 0; --i)
		{
			for (int j = N - 1; j >= 0; --j)
			{
                if (A[i][j] != 0) 
                {
                    continue;
                }
                int leftCount = 0;
                for (int x = 0; x < j; ++x) 
                {
                    if (A[i][x] != 0) 
                    {
						leftCount++;
                    }
                }
				if (leftCount != left[i][j]) 
                {
                    continue;
                }
                int topCount = 0;
                for (int y = 0; y < i; ++y) 
                {
                    if (A[y][j] != 0) 
                    {
						topCount++;
                    }
                }
				if (topCount != top[i][j]) 
                {
                    continue;
                }
                A[i][j] = k;
                found = true;
                break;
            }
            if (found) 
            {
                break;
            }
        }
        if (!found) 
        {
			outputFile << 0 << std::endl;
			std::cout << "Matrix could not be found" << std::endl;
            return 0;
        }
    }
	std::cout << "The matrix was successfully determined" << std::endl;
	PrintMatrix(A, N, outputFile);

    auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << std::endl;

    return 0;
}

