/*
3.8. Числа (5).
Составляются N-значные числа (1 ≤ N ≤ 32) из цифр 1, 2, 3, 4, 5 по следующим правилам:
цифра 1 не может стоять в крайнем левом и крайнем правом разрядах;
в числе не может быть двух одинаковых цифр стоящих рядом;
цифра 1 может присутсвовать в числе только между двумя разными разрядами.
Сколько таких чисел при заданном значении N?
Ввод.  В единственной строке находится число N.
Вывод. В единственной строке вывести количество искомых чисел.
Примеры
Ввод 1      Ввод 2
1           2
Вывод 1     Вывод 2
4           12


ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Microsoft Visual Studio 2022
*/


#include <iostream>
#include <fstream> 
#include <vector>
#include <climits>


unsigned long long CounNumbersVariant(int N)
{
	std::vector<unsigned long long> A(N + 1);
	// вектор с количеством чисел не заканчивающиеся для N, согласно условию
	std::vector<unsigned long long> B(N + 1);
	// вектор с количеством чисел заканчивающиеся для N, согласно условию

	A[1] = 4;
	B[1] = 0;

	for (int n = 2; n <= N; ++n)
	{
		if (A[n - 1] > ULLONG_MAX / 3 || 4 * B[n - 1] > ULLONG_MAX - 3 * A[n - 1])
		{
			return 0;
		}

		A[n] = 3 * A[n - 1] + 4 * B[n - 1];
		B[n] = A[n - 1];
	}

	return A[N];
}

int main()
{
	std::ifstream inputFile("INPUT.TXT");
	std::ofstream outputFile("OUTPUT.TXT");


	int N;
	inputFile >> N;

	if (N < 1 || N > 32)
	{
		outputFile << "Число не входит в диапазон\n";
	}
	else 
	{
		unsigned long long countNumbers = CounNumbersVariant(N);

		if (countNumbers == 0)
		{
			outputFile << "Произошло переполнение\n";
			return 1;
		}

		outputFile << "Количество вариантов: " << countNumbers << std::endl;
	}
	
	return 0;
}