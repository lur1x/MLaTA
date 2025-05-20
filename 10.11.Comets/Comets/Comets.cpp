/*
10.11. Кометы (6)
Астроном Коперни увлечен кометами. Он определил новую физическую единицу яркости Co и вывел закон
нахождения яркости комет в зависимости от времени в виде Y = At + B. В дальнейших исследованиях ему
удалось рассчитать коэффициенты A и B для всех известных комет. Коперни в любой момент времени 
всегда наблюдает в свой телескоп комету с наибольшей яркостью. Как только у другой кометы яркость 
оказывается большей, он переносит на нее свои наблюдения. Для заказа нового телескопа ему необходимо 
знать минимальную яркость наблюдаемой им кометы на определенный период времени. Помогите астроному 
Коперни.
Ввод из файла INPUT.TXT. В первой строке указаны N и T (1 ≤ N, T ≤ 2000) – число комет и период 
наблюдения. В следующих N строках содержатся коэффициенты Ai и Bi (-100 ≤ Ai, Bi ≤ 100) для всех 
N комет. Все числа N, T, Ai, Bi целые. Необходимо иметь в виду, что яркость кометы в единицах Co
может быть как положительной, так и отрицательной.
Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальную яркость кометы, которую будет 
наблюдать астрономом в период от 0 до T с точностью 10 знаков после запятой.
Пример
Ввод
2 4
1 1
-1 5
Вывод
3.0000000000


ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22

*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

double CalculateMax(const std::vector<std::pair<int, int>>& comets, double t)
{
	double max = -1e18;
	for (const auto& comet : comets)
	{
		double y = comet.first * t + comet.second;
		if (y > max)
		{
			max = y;
		}
	}
	return max;
}

double TernarySearch(const std::vector<std::pair<int, int>>& comets, double left, double right, double precision)
{
	while (right - left > precision)
	{
		double mid1 = left + (right - left) / 3.0;
		double mid2 = right - (right - left) / 3.0;

		double y1 = CalculateMax(comets, mid1);
		double y2 = CalculateMax(comets, mid2);

		if (y1 < y2)
		{
			right = mid2;
		}
		else
		{
			left = mid1;
		}
		
	}
	return CalculateMax(comets, left);
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream input("INPUT.TXT");
	std::ofstream ouput("OUTPUT.TXT");

	int N, T;
	input >> N >> T;
	std::vector<std::pair<int, int>> comets(N);

	for (int i = 0; i < N; ++i)
	{
		input >> comets[i].first >> comets[i].second;
	}

	const double precision = 1e-12;

	double left = 0.0;
	double right = T;
	

	double minMax = TernarySearch(comets, left, right, precision);

	ouput << std::fixed << std::setprecision(10) << minMax << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Время выполнения: " << duration.count() << std::endl;

	return 0;
}