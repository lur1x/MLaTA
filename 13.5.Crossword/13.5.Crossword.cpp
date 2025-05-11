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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>


std::vector<std::string> words(4);
int min_area = INT_MAX;
std::vector<std::string> best_crossword;

void СheckСrossword(int h1_y, int h1_x, int h2_y, int h2_x, int v1_x, int v1_y, int v2_x, int v2_y) 
{
    // Определяем границы кроссворда
    int min_x = std::min({ 
        h1_x, 
        h2_x, 
        v1_x, 
        v2_x 
    });
    int max_x = std::max({ 
        h1_x + (int)words[0].size() - 1,
        h2_x + (int)words[1].size() - 1,
        v1_x, 
        v2_x 
    });
    int min_y = std::min({ 
        h1_y, 
        h2_y, 
        v1_y, 
        v2_y 
    });
    int max_y = std::max({ 
        h1_y, 
        h2_y,
        v1_y + (int)words[2].size() - 1,
        v2_y + (int)words[3].size() - 1 
    });

    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;
    int area = width * height;

    // Если площадь больше уже найденной минимальной, пропускаем
    if (area > min_area)
    {
        return;
    }
    // Создаем сетку кроссворда
    std::vector< std::string> grid(height, std::string(width, '*'));

    // Размещаем горизонтальные слова
    for (int i = 0; i < words[0].size(); ++i) 
    {
        int y = h1_y - min_y;
        int x = h1_x - min_x + i;
        if (grid[y][x] != '*' && grid[y][x] != words[0][i])
        {
            return;
        }
        grid[y][x] = words[0][i];
    }

    for (int i = 0; i < words[1].size(); ++i) 
    {
        int y = h2_y - min_y;
        int x = h2_x - min_x + i;
        if (grid[y][x] != '*' && grid[y][x] != words[1][i]) 
        {
            return;
        }
        grid[y][x] = words[1][i];
    }

    // Размещаем вертикальные слова
    for (int i = 0; i < words[2].size(); ++i) 
    {
        int y = v1_y - min_y + i;
        int x = v1_x - min_x;
        if (grid[y][x] != '*' && grid[y][x] != words[2][i])
        {
            return;
        }
        grid[y][x] = words[2][i];
    }

    for (int i = 0; i < words[3].size(); ++i) 
    {
        int y = v2_y - min_y + i;
        int x = v2_x - min_x;
        if (grid[y][x] != '*' && grid[y][x] != words[3][i])
        {
            return;
        }
        grid[y][x] = words[3][i];
    }

    // Проверяем пересечения
    bool h1_v1 = false, 
        h1_v2 = false,
        h2_v1 = false, 
        h2_v2 = false;

    for (int i = 0; i < words[0].size(); ++i) 
    {
        int y = h1_y - min_y;
        int x = h1_x - min_x + i;
        if (x == v1_x - min_x && y >= v1_y - min_y && y < v1_y - min_y + (int)words[2].size()) 
        {
            h1_v1 = true;
        }
        if (x == v2_x - min_x && y >= v2_y - min_y && y < v2_y - min_y + (int)words[3].size()) 
        {
            h1_v2 = true;
        }
    }

    for (int i = 0; i < words[1].size(); ++i) 
    {
        int y = h2_y - min_y;
        int x = h2_x - min_x + i;
        if (x == v1_x - min_x && y >= v1_y - min_y && y < v1_y - min_y + (int)words[2].size()) 
        {
            h2_v1 = true;
        }
        if (x == v2_x - min_x && y >= v2_y - min_y && y < v2_y - min_y + (int)words[3].size()) 
        {
            h2_v2 = true;
        }
    }

    if (!h1_v1 || !h1_v2 || !h2_v1 || !h2_v2)
    {
        return;
    }
    // Если нашли решение с меньшей площадью, обновляем
    if (area < min_area) 
    {
        min_area = area;
        best_crossword = grid;
    }
}

int main()
{
    std::ifstream input_file("INPUT.TXT");
    std::ofstream output_file("OUTPUT.TXT");

    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 4; ++i) 
    {
        input_file >> words[i];
    }

    // Проверяем все возможные пересечения между словами
    // Горизонтальные слова: words[0] и words[1] (words[0] выше words[1])
    // Вертикальные слова: words[2] и words[3] (words[2] левее words[3])

    // Перебираем все возможные пересечения words[0] с words[2]
    for (int h1_pos = 0; h1_pos < words[0].size(); ++h1_pos) 
    {
        for (int v1_pos = 0; v1_pos < words[2].size(); ++v1_pos) 
        {
            if (words[0][h1_pos] != words[2][v1_pos])
            {
                continue;
            }
            // Перебираем все возможные пересечения words[0] с words[3]
            for (int h1_pos2 = 0; h1_pos2 < words[0].size(); ++h1_pos2) 
            {
                if (h1_pos2 == h1_pos)
                {
                    continue; // чтобы не пересекались в одной точке
                }
                for (int v2_pos = 0; v2_pos < words[3].size(); ++v2_pos) 
                {
                    if (words[0][h1_pos2] != words[3][v2_pos])
                    {
                        continue;
                    }
                    // Перебираем все возможные пересечения words[1] с words[2]
                    for (int h2_pos = 0; h2_pos < words[1].size(); ++h2_pos) 
                    {
                        for (int v1_pos2 = 0; v1_pos2 < words[2].size(); ++v1_pos2) 
                        {
                            if (v1_pos2 == v1_pos)
                            {
                                continue; // чтобы не пересекались в одной точке
                            }
                            if (words[1][h2_pos] != words[2][v1_pos2])
                            {
                                continue;
                            }
                            // Перебираем все возможные пересечения words[1] с words[3]
                            for (int h2_pos2 = 0; h2_pos2 < words[1].size(); ++h2_pos2) 
                            {
                                if (h2_pos2 == h2_pos)
                                {
                                    continue; // чтобы не пересекались в одной точке
                                }
                                for (int v2_pos2 = 0; v2_pos2 < words[3].size(); ++v2_pos2) 
                                {
                                    if (v2_pos2 == v2_pos)
                                    {
                                        continue; // чтобы не пересекались в одной точке
                                    }
                                    if (words[1][h2_pos2] != words[3][v2_pos2])
                                    {
                                        continue;
                                    }
                                    // Вычисляем координаты слов
                                    // words[0] (h1) пересекает words[2] (v1) в (h1_x + h1_pos, h1_y) = (v1_x, v1_y + v1_pos)
                                    // words[0] (h1) пересекает words[3] (v2) в (h1_x + h1_pos2, h1_y) = (v2_x, v2_y + v2_pos)
                                    // words[1] (h2) пересекает words[2] (v1) в (h2_x + h2_pos, h2_y) = (v1_x, v1_y + v1_pos2)
                                    // words[1] (h2) пересекает words[3] (v2) в (h2_x + h2_pos2, h2_y) = (v2_x, v2_y + v2_pos2)

                                    // Решаем систему уравнений для координат
                                    // h1_x + h1_pos = v1_x
                                    // h1_y = v1_y + v1_pos
                                    // h1_x + h1_pos2 = v2_x
                                    // h1_y = v2_y + v2_pos
                                    // h2_x + h2_pos = v1_x
                                    // h2_y = v1_y + v1_pos2
                                    // h2_x + h2_pos2 = v2_x
                                    // h2_y = v2_y + v2_pos2

                                    // Из первых двух уравнений:
                                    // v1_x = h1_x + h1_pos
                                    // v1_y = h1_y - v1_pos

                                    // Из третьего и четвертого:
                                    // v2_x = h1_x + h1_pos2
                                    // v2_y = h1_y - v2_pos

                                    // Из пятого и шестого:
                                    // h2_x = v1_x - h2_pos = h1_x + h1_pos - h2_pos
                                    // h2_y = v1_y + v1_pos2 = h1_y - v1_pos + v1_pos2

                                    // Из седьмого и восьмого:
                                    // h2_x = v2_x - h2_pos2 = h1_x + h1_pos2 - h2_pos2
                                    // h2_y = v2_y + v2_pos2 = h1_y - v2_pos + v2_pos2

                                    // Приравниваем выражения для h2_x:
                                    // h1_x + h1_pos - h2_pos = h1_x + h1_pos2 - h2_pos2
                                    // => h1_pos - h2_pos = h1_pos2 - h2_pos2
                                    // => h1_pos - h1_pos2 = h2_pos - h2_pos2
                                    // Это должно выполняться, иначе решения нет

                                    if (h1_pos - h1_pos2 != h2_pos - h2_pos2)
                                    {
                                        continue;
                                    }
                                    // Приравниваем выражения для h2_y:
                                    // h1_y - v1_pos + v1_pos2 = h1_y - v2_pos + v2_pos2
                                    // => -v1_pos + v1_pos2 = -v2_pos + v2_pos2
                                    // => v1_pos2 - v1_pos = v2_pos2 - v2_pos
                                    // Это должно выполняться, иначе решения нет

                                    if (v1_pos2 - v1_pos != v2_pos2 - v2_pos) 
                                    {
                                        continue;
                                    }
                                    // Теперь можем выбрать h1_x и h1_y произвольно (например, 0, 0)
                                    // и вычислить все остальные координаты
                                    int h1_x = 0;
                                    int h1_y = 0;

                                    int v1_x = h1_x + h1_pos;
                                    int v1_y = h1_y - v1_pos;

                                    int v2_x = h1_x + h1_pos2;
                                    int v2_y = h1_y - v2_pos;

                                    int h2_x = v1_x - h2_pos;
                                    int h2_y = v1_y + v1_pos2;

                                    // Проверяем, что words[1] действительно ниже words[0]
                                    if (h2_y <= h1_y)
                                    {
                                        continue;
                                    }
                                    // Проверяем, что words[3] действительно правее words[2]
                                    if (v2_x <= v1_x)
                                    {
                                        continue;
                                    }
                                    // Проверяем корректность размещения слов
                                    СheckСrossword(h1_y, h1_x, h2_y, h2_x, v1_x, v1_y, v2_x, v2_y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
   

    if (min_area == INT_MAX)
    {
        output_file << "No" << std::endl;
    }
    else 
    {
        for (const  std::string& row : best_crossword)
        {
            output_file << row << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Time: " << duration.count() << std::endl;

    return 0;
}