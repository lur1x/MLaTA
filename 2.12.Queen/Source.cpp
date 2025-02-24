#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Структура для хранения состояния поиска
struct State
{
	vector<int> board; // Текущая расстановка ферзей
};

// Функция для проверки, можно ли поставить ферзя на позицию (row, col)
bool isSafe(int row, int col, const vector<int>& board)
{
	for (int i = 0; i < row; ++i)
	{
		if (board[i] == col || abs(board[i] - col) == abs(i - row))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	ifstream input("INPUT.TXT");
	ofstream output("OUTPUT.TXT");

	int n;
	input >> n;

	vector<vector<string>> solutions; // Список всех решений
	queue<State> queue; // Очередь для BFS

	// Начальное состояние: пустая доска
	State initial;
	initial.board.resize(n, -1);
	queue.push(initial);

	while (!queue.empty())
	{
		State current = queue.front();
		queue.pop();

		int row = 0;
		// Находим первую незаполненную строку
		while (row < n && current.board[row] != -1)
		{
			row++;
		}

		// Если все строки заполнены, добавляем решение
		if (row == n)
		{
			vector<string> solution;
			for (int i = 0; i < n; ++i)
			{
				string pos = "";
				pos += ('a' + current.board[i]);
				pos += to_string(i + 1);
				solution.push_back(pos);
			}
			solutions.push_back(solution);
			continue;
		}

		// Пробуем поставить ферзя в каждый столбец текущей строки
		for (int col = 0; col < n; ++col)
		{
			if (isSafe(row, col, current.board))
			{
				State nextState = current;
				nextState.board[row] = col;
				queue.push(nextState);
			}
		}
	}

	// Вывод всех решений
	for (const auto& solution : solutions)
	{
		for (const auto& pos : solution)
		{
			output << pos << " ";
		}
		output << endl;
	}

	// Вывод количества решений
	output << solutions.size() << " positions" << endl;

	input.close();
	output.close();

	return 0;
}