/*
13.5. Кроссворд (8)
Заданы четыре слова, в каждом из которых нет повторяющихся букв. Требуется составить минимальный по
количеству клеток прямоугольный кроссворд, в котором два первых слова расположены горизонтально, и 
первое выше второго, а два последних вертикально, и третье левее четвертого. Каждое горизонтальное 
слово должно пересекаться с обоими вертикальными словами.
Ввод из файла INPUT.TXT. В первых четырех строках записаны слова, состоящие из заглавных латинских 
букв. Длина каждого слова до 20 символов.
Вывод в файл OUTPUT.TXT. Вывести кроссворд в виде прямоугольника из минимального количества клеток. 
Проставить звездочки в те позиции, где нет букв. Левый край кроссворда должен быть в первой позиции, 
а верхний край - в первой строке. Если решений несколько, вывести любое из них. При отсутствии 
решений вывести No.

Пример:

Ввод
STAMPING
FORMULA
STOP
SPELING

Вывод
*****S***
*STAMPING
*T***E***
FORMULA**
*P***I***
*****N***
*****G***

ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22

*/

#include <algorithm>
#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Words(4);
int MinArea = INT_MAX;
std::vector<std::string> BestCrossword;

void CheckCrossword(int firstHorizontalY, int firstHorizontalX,
	int secondHorizontalY, int secondHorizontalX,
	int firstVerticalX, int firstVerticalY,
	int secondVerticalX, int secondVerticalY)
{
	// Определяем границы кроссворда
	int minX = std::min({ firstHorizontalX, secondHorizontalX, firstVerticalX, secondVerticalX });
	int maxX = std::max({ firstHorizontalX + (int)Words[0].size() - 1,
		secondHorizontalX + (int)Words[1].size() - 1,
		firstVerticalX, secondVerticalX });
	int minY = std::min({ firstHorizontalY, secondHorizontalY, firstVerticalY, secondVerticalY });
	int maxY = std::max({ firstHorizontalY, secondHorizontalY,
		firstVerticalY + (int)Words[2].size() - 1,
		secondVerticalY + (int)Words[3].size() - 1 });

	int width = maxX - minX + 1;
	int height = maxY - minY + 1;
	int area = width * height;

	if (area > MinArea)
		return;

	std::vector<std::string> grid(height, std::string(width, '*'));

	// Размещаем горизонтальные слова
	for (int i = 0; i < Words[0].size(); ++i)
	{
		int y = firstHorizontalY - minY;
		int x = firstHorizontalX - minX + i;
		if (grid[y][x] != '*' && grid[y][x] != Words[0][i])
			return;
		grid[y][x] = Words[0][i];
	}

	for (int i = 0; i < Words[1].size(); ++i)
	{
		int y = secondHorizontalY - minY;
		int x = secondHorizontalX - minX + i;
		if (grid[y][x] != '*' && grid[y][x] != Words[1][i])
			return;
		grid[y][x] = Words[1][i];
	}

	// Размещаем вертикальные слова
	for (int i = 0; i < Words[2].size(); ++i)
	{
		int y = firstVerticalY - minY + i;
		int x = firstVerticalX - minX;
		if (grid[y][x] != '*' && grid[y][x] != Words[2][i])
			return;
		grid[y][x] = Words[2][i];
	}

	for (int i = 0; i < Words[3].size(); ++i)
	{
		int y = secondVerticalY - minY + i;
		int x = secondVerticalX - minX;
		if (grid[y][x] != '*' && grid[y][x] != Words[3][i])
			return;
		grid[y][x] = Words[3][i];
	}

	// Проверяем пересечения
	bool firstHorizontalFirstVertical = false;
	bool firstHorizontalSecondVertical = false;
	bool secondHorizontalFirstVertical = false;
	bool secondHorizontalSecondVertical = false;

	for (int i = 0; i < Words[0].size(); ++i)
	{
		int y = firstHorizontalY - minY;
		int x = firstHorizontalX - minX + i;
		if (x == firstVerticalX - minX && y >= firstVerticalY - minY && y < firstVerticalY - minY + (int)Words[2].size())
		{
			firstHorizontalFirstVertical = true;
		}
		if (x == secondVerticalX - minX && y >= secondVerticalY - minY && y < secondVerticalY - minY + (int)Words[3].size())
		{
			firstHorizontalSecondVertical = true;
		}
	}

	for (int i = 0; i < Words[1].size(); ++i)
	{
		int y = secondHorizontalY - minY;
		int x = secondHorizontalX - minX + i;
		if (x == firstVerticalX - minX && y >= firstVerticalY - minY && y < firstVerticalY - minY + (int)Words[2].size())
		{
			secondHorizontalFirstVertical = true;
		}
		if (x == secondVerticalX - minX && y >= secondVerticalY - minY && y < secondVerticalY - minY + (int)Words[3].size())
		{
			secondHorizontalSecondVertical = true;
		}
	}

	if (!firstHorizontalFirstVertical || !firstHorizontalSecondVertical || !secondHorizontalFirstVertical || !secondHorizontalSecondVertical)
	{
		return;
	}

	if (area < MinArea)
	{
		MinArea = area;
		BestCrossword = grid;
	}
}

int main()
{
	std::ifstream inputFile("INPUT.TXT");
	std::ofstream outputFile("OUTPUT.TXT");

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 4; ++i)
	{
		inputFile >> Words[i];
	}

	// Перебираем все возможные пересечения между словами

	// Перебираем все возможные пересечения words[0] с words[2]
	for (int firstHorizontalFirstVerticalPos = 0;
		firstHorizontalFirstVerticalPos < Words[0].size();
		++firstHorizontalFirstVerticalPos)
	{
		for (int firstVerticalPos = 0; firstVerticalPos < Words[2].size(); ++firstVerticalPos)
		{
			if (Words[0][firstHorizontalFirstVerticalPos] != Words[2][firstVerticalPos])
			{
				continue;
			} 
			// Перебираем все возможные пересечения words[0] с words[3]
			for (int firstHorizontalSecondVerticalPos = 0;
				firstHorizontalSecondVerticalPos < Words[0].size();
				++firstHorizontalSecondVerticalPos)
			{
				if (firstHorizontalSecondVerticalPos == firstHorizontalFirstVerticalPos)
				{
					continue; // чтобы не пересекались в одной точке
				}
				for (int secondVerticalPos = 0; secondVerticalPos < Words[3].size(); ++secondVerticalPos)
				{
					if (Words[0][firstHorizontalSecondVerticalPos] != Words[3][secondVerticalPos])
					{
						continue;
					}
					// Перебираем все возможные пересечения words[1] с words[2]
					for (int secondHorizontalFirstVerticalPos = 0;
						secondHorizontalFirstVerticalPos < Words[1].size();
						++secondHorizontalFirstVerticalPos)
					{
						for (int firstVerticalPos2 = 0; firstVerticalPos2 < Words[2].size(); ++firstVerticalPos2)
						{
							if (firstVerticalPos2 == firstVerticalPos)
							{
								continue;
							}
							
							if (Words[1][secondHorizontalFirstVerticalPos] != Words[2][firstVerticalPos2])
							{
								continue;
							}
							// Перебираем все возможные пересечения words[1] с words[3]
							for (int secondHorizontalSecondVerticalPos = 0;
								secondHorizontalSecondVerticalPos < Words[1].size();
								++secondHorizontalSecondVerticalPos)
							{
								if (secondHorizontalSecondVerticalPos == secondHorizontalFirstVerticalPos)
								{
									continue;
								}
								for (int secondVerticalPos2 = 0; secondVerticalPos2 < Words[3].size(); ++secondVerticalPos2)
								{
									if (secondVerticalPos2 == secondVerticalPos)
									{
										continue;
									}
									if (Words[1][secondHorizontalSecondVerticalPos] != Words[3][secondVerticalPos2])
									{
										continue;
									}
									// Проверяем условия согласованности
									if (firstHorizontalFirstVerticalPos - firstHorizontalSecondVerticalPos != secondHorizontalFirstVerticalPos - secondHorizontalSecondVerticalPos)
									{
										continue;
									}

									if (firstVerticalPos2 - firstVerticalPos != secondVerticalPos2 - secondVerticalPos)
									{
										continue;
									}

									// Устанавливаем базовые координаты
									int firstHorizontalX = 0;
									int firstHorizontalY = 0;

									int firstVerticalX = firstHorizontalX + firstHorizontalFirstVerticalPos;
									int firstVerticalY = firstHorizontalY - firstVerticalPos;

									int secondVerticalX = firstHorizontalX + firstHorizontalSecondVerticalPos;
									int secondVerticalY = firstHorizontalY - secondVerticalPos;

									int secondHorizontalX = firstVerticalX - secondHorizontalFirstVerticalPos;
									int secondHorizontalY = firstVerticalY + firstVerticalPos2;

									// Проверяем расположение слов
									if (secondHorizontalY <= firstHorizontalY)
										continue;
									if (secondVerticalX <= firstVerticalX)
										continue;

									CheckCrossword(firstHorizontalY, firstHorizontalX,
										secondHorizontalY, secondHorizontalX,
										firstVerticalX, firstVerticalY,
										secondVerticalX, secondVerticalY);
								}
							}
						}
					}
				}
			}
		}
	}

	if (MinArea == INT_MAX)
	{
		outputFile << "No" << std::endl;
	}
	else
	{
		for (const std::string& row : BestCrossword)
		{
			outputFile << row << std::endl;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << std::endl;

	return 0;
}