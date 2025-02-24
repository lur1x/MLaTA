/* 2.12. Ферзи (7)
Методом поиска в ширину расставить на шахматной доске размером N × N  клеток N  ферзей
(1 ≤ N ≤ 12) так, чтобы они не атаковали один другого. Иными словами, они должны стоять
на разных горизонталях, вертикалях и диагоналях.
Ввод из файла INPUT.TXT. В единственной строке задается значение N.
Вывод в файл OUTPUT.TXT. Вывести все искомые позиции, используя шахматные обозначениях.
Горизонтали доски нумеруются от 1 до N. Вертикали обозначаются строчными лаьтнскими буквами
‘a‘,‘b‘,‘c‘ и т. д. Поля в позиции должны следовать по возрастанию номера столбца
(буквы по алфавиту), а сами позиции по возрастанию строк, которые их представляют.
В последней строке сообщить о количестве найденных позиций.

Примеры
Ввод 1        Ввод 2        Ввод 3
4             1             3
Вывод 1       Вывод 2       Вывод 3
a2 b4 c1 d3   a1            0 positions
a3 b1 c4 d2   1 positions
2 positions

ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22
*/


#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <vector>
#include <queue>
#include <string>


struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

struct State
{
	std::vector<int> board; 
};

Args ParseArgs(int argc, char** argv)
{
    if (argc != 3)
    {
        throw std::runtime_error("Invalid arguments count \n Usage: queen.exe <input file> <output file>");
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    return args;
}

unsigned int ReadSizeСhessboard(std::ifstream& file)
{
	unsigned int boardSize;
	file >> boardSize; 
	if (boardSize < 1 || boardSize > 12)
	{
		throw std::runtime_error("Invalid character: The board size can be in the range 1 <= N <= 12");
	}
	if (file.bad())
	{
		throw std::runtime_error("Error reading input file");
	}
	return boardSize;
}

void AddSolution(std::vector<std::vector<std::string>>& solutions, State& current, const unsigned int n)
{
	std::vector<std::string> solution;
	for (unsigned int i = 0; i < n; ++i)
	{
		std::string pos = "";
		pos += ('a' + i); 
		pos += std::to_string(current.board[i] + 1); 
		solution.push_back(pos);
	}
	solutions.push_back(solution);
}

bool IsSafe(int row, int col, const std::vector<int>& board)
{
	for (size_t i = 0; i < row; ++i)
	{
		if (board[i] == col || abs(board[i] - col) == abs(static_cast<int>(i) - row))
		{
			return false;
		}
	}
	return true;
}

void TryToPlaceQueen(std::queue<State>& queue, State& current, unsigned int n, unsigned int row)
{
	for (unsigned int col = 0; col < n; ++col)
	{
		if (IsSafe(row, col, current.board))
		{
			State nextState = current;
			nextState.board[row] = col;
			queue.push(nextState);
		}
	}
}

bool IsFullChessboard(const unsigned int row, const unsigned int n)
{
	if (row == n)
	{
		return true;
	}
	return false;
}

void FindPositionsQueens(std::vector<std::vector<std::string>>& solutions, std::queue<State>& queue, unsigned int n)
{
	while (!queue.empty())
	{
		State current = queue.front();
		queue.pop();

		unsigned int row = 0; 

		while (row < n && current.board[row] != -1)
		{

			row++;
		}

		if (IsFullChessboard(row, n))
		{
			AddSolution(solutions, current, n);
			continue;
		}

		TryToPlaceQueen(queue, current, n, row);
	}
}

void PrintSolutionsInFile(std::vector<std::vector<std::string>>& solutions, std::ofstream& outputFile)
{
	for (const auto& solution : solutions)
	{
		for (const auto& pos : solution)
		{
			outputFile << pos << " ";
		}
		outputFile << std::endl;
	}
}

void HandleSizeChessboard(const std::string& inputFilePath, const std::string& outputFilePath)
{
	std::ifstream inputFile(inputFilePath);
	std::ofstream outputFile(outputFilePath);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	unsigned int sizeСhessboard = ReadSizeСhessboard(inputFile);
	
	std::vector<std::vector<std::string>> solutions; 
	std::queue<State> queue; 

	State initial;
	initial.board.resize(sizeСhessboard, -1);
	queue.push(initial);
	
	FindPositionsQueens(solutions, queue, sizeСhessboard);

	PrintSolutionsInFile(solutions, outputFile);
	outputFile << solutions.size() << " positions\n";

}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		auto start = std::chrono::high_resolution_clock::now();

		HandleSizeChessboard(args.inputFileName, args.outputFileName);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << duration.count() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;

}
