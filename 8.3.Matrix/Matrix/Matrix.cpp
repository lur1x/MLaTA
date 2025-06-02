/*
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

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip> 

using Matrix = std::vector<std::vector<int>>;
using Position = std::pair<int, int>;

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

	int N;
	inputFile >> N;

    Matrix top(N, std::vector<int>(N));
	ReadMatrix(top, N, inputFile);

	Matrix left(N, std::vector<int>(N));
	ReadMatrix(left, N, inputFile);

	Matrix A(N, std::vector<int>(N, 0));

	auto start = std::chrono::high_resolution_clock::now();

	for (int num = 1; num <= N * N; ++num)
	{
		std::vector<Position> rowСandidates;
		std::vector<Position> colСandidates;

		for (int i = 0; i < N; ++i)
		{
			for (int j = N - 1; j >= 0; --j)
			{
				if (left[i][j] == j && A[i][j] == 0)
				{
					rowСandidates.emplace_back(i, j);
					break;
				}
			}
		}

		for (int j = 0; j < N; ++j)
		{
			for (int i = N - 1; i >= 0; --i)
			{
				if (top[i][j] == i && A[i][j] == 0)
				{
					colСandidates.emplace_back(i, j);
					break;
				}
			}
		}

		Position pos = { -1, -1 };
		for (auto rc : rowСandidates)
		{
			for (auto cc : colСandidates)
			{
				if (rc == cc)
				{
					pos = rc;
					break;
				}
			}
			if (pos.first != -1)
				break;
		}

		if (pos.first == -1)
		{
			if (!rowСandidates.empty())
			{
				pos = rowСandidates[0];
			}
			else if (!colСandidates.empty())
			{
				pos = colСandidates[0];
			}
			else
			{
				outputFile << 0 << std::endl;
				std::cout << "Matrix could not be found" << std::endl;
				return 0;
			}
		}

		int i = pos.first, j = pos.second;
		A[i][j] = num;

		top[i][j] = -1;
		left[i][j] = -1;

		for (int k = j + 1; k < N; ++k)
		{
			if (left[i][k] != -1)
				left[i][k]++;
		}
		for (int k = i + 1; k < N; ++k)
		{
			if (top[k][j] != -1)
				top[k][j]++;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << std::endl;

	std::cout << "The matrix was successfully determined" << std::endl;
	PrintMatrix(A, N, outputFile);

	inputFile.close();
	outputFile.close();

	return 0;
}