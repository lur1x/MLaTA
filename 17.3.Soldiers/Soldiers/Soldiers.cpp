/*
17.3. Построение (7)
В одной военной части построили солдат в одну шеренгу по убыванию роста. Часть была далеко не
образцовая. Солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из строя за 
плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода всегда должны быть выстроены по
росту. Требуется для каждого приходящего солдата указывать, перед каким солдатом в строю он должен 
становиться. Если пришедший солдат одинакового роста с некоторыми солдатами в строю, то он 
становится сразу после них.
Ввод из файла INPUT.TXT. Первая строка содержит количество команд N (1 ≤  N ≤ 200000). В каждой 
следующей строке содержится описание команды: числа 1 и X, если солдат приходит в строй (X – рост 
солдата от 1 до 100000) и числа 2 и Y, если солдата, стоящего в строю на месте Y надо удалить из 
строя. Солдаты в строю нумеруются с 1.
Вывод в файл OUTPUT.TXT. На каждую команду 1 (добавление в строй) нужно выводить в отдельной строке 
число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).

Пример:

Ввод
5
1 100
1 200
1 50
2 1
1 150

Вывод
1
1
3
1



ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22

*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <chrono>

#include "FenwickTree.h"

void ReadCommandFile(std::ifstream& input, const int& N, std::vector<std::pair<int, int>>& commands, std::vector<int>& allHeights)
{
	for (int i = 0; i < N; ++i)
	{
		int command, value;
		input >> command >> value;
		commands.push_back({ command, value });
		if (command == 1)
		{
			allHeights.push_back(value);
		}
	}
}

int main()
{
	std::ifstream input("INPUT.TXT");
	std::ofstream output("OUTPUT.TXT");

	int N;
	input >> N;

	std::vector<std::pair<int, int>> commands;
	std::vector<int> allHeights;

	auto start = std::chrono::high_resolution_clock::now();

	ReadCommandFile(input, N, commands, allHeights);

	std::sort(allHeights.begin(), allHeights.end(), std::greater<int>());
	allHeights.erase(unique(allHeights.begin(), allHeights.end()), allHeights.end());

	std::map<int, int> universal;
	for (int i = 0; i < allHeights.size(); ++i)
	{
		universal[allHeights[i]] = i + 1;
	}

	FenwickTree fenwick(allHeights.size());

	for (const auto& cmd : commands)
	{
		int command = cmd.first;
		int value = cmd.second;

		if (command == 1)
		{
			int pos = universal[value];
			int k = fenwick.Query(pos);
			output << (k + 1) << "\n";
			fenwick.Update(pos, 1);
		}
		else if (command == 2)
		{
			int pos = fenwick.FindPosition(value);
			if (pos > 0)
			{
				fenwick.Update(pos, -1);
			}
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << std::endl;

	input.close();
	output.close();
	return 0;
}