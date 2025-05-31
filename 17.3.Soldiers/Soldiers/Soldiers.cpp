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
#include <vector>

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

	// Бинарный поиск первого индекса, где сумма >= target
	int find(int target)
	{
		int left = 1, right = tree.size() - 1;
		int pos = 0;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			int sum = query(mid);
			if (sum >= target)
			{
				pos = mid;
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return pos;
	}
};

int main()
{
	ifstream input("INPUT.TXT");
	ofstream output("OUTPUT.TXT");

	int N;
	input >> N;

	// Для хранения всех возможных ростов и их порядка
	vector<int> all_heights;
	vector<pair<int, int>> commands;

	// Считываем все команды и собираем все возможные роста
	for (int i = 0; i < N; ++i)
	{
		int command, value;
		input >> command >> value;
		commands.push_back({ command, value });
		if (command == 1)
		{
			all_heights.push_back(value);
		}
	}

	// Сортируем и удаляем дубликаты
	sort(all_heights.begin(), all_heights.end(), greater<int>());
	all_heights.erase(unique(all_heights.begin(), all_heights.end()), all_heights.end());

	// Создаем отображение рост -> сжатый индекс
	map<int, int> compressed;
	for (int i = 0; i < all_heights.size(); ++i)
	{
		compressed[all_heights[i]] = i + 1;
	}

	FenwickTree fenwick(all_heights.size());

	for (const auto& cmd : commands)
	{
		int command = cmd.first;
		int value = cmd.second;

		if (command == 1)
		{
			// Вставка солдата
			int pos = compressed[value];
			// Количество солдат с ростом >= текущего
			int k = fenwick.query(pos);
			output << (k + 1) << "\n";
			fenwick.update(pos, 1);
		}
		else if (command == 2)
		{
			// Удаление солдата с позиции value
			int pos = fenwick.find(value);
			if (pos > 0)
			{
				fenwick.update(pos, -1);
			}
		}
	}

	return 0;
}