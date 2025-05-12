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
#include <vector>
#include <chrono>

using namespace std;

class FenwickTree
{
private:
	vector<int> tree;

public:
	FenwickTree(int size)
		: tree(size + 1, 0)
	{
	}

	void update(int index, int delta)
	{
		for (; index < tree.size(); index += index & -index)
		{
			tree[index] += delta;
		}
	}

	int query(int index)
	{
		int res = 0;
		for (; index > 0; index -= index & -index)
		{
			res += tree[index];
		}
		return res;
	}

	int findPosition(int sum)
	{
		int bitMask = 1 << 20;
		int index = 0;
		while (bitMask != 0)
		{
			int nextIndex = index + bitMask;
			if (nextIndex < tree.size() && tree[nextIndex] < sum)
			{
				sum -= tree[nextIndex];
				index = nextIndex;
			}
			bitMask >>= 1;
		}
		return index + 1;
	}
};

int main()
{
	ifstream input("INPUT.TXT");
	ofstream output("OUTPUT.TXT");

	auto start = std::chrono::high_resolution_clock::now();

	int N;
	input >> N;

	FenwickTree fenwick(200000);
	vector<int> soldiers;

	for (int i = 0; i < N; ++i)
	{
		int command, value;
		input >> command >> value;

		if (command == 1)
		{
			// Вставка солдата
			int pos = fenwick.query(200000) - fenwick.query(value) + 1;
			output << pos << endl;
			soldiers.insert(soldiers.begin() + (pos - 1), value);
			fenwick.update(value, 1);
		}
		else
		{
			// Удаление солдата
			int height = soldiers[value - 1];
			fenwick.update(height, -1);
			soldiers.erase(soldiers.begin() + (value - 1));
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << std::endl;

	return 0;
}