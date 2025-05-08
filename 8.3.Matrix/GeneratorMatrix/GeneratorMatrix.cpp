#include <iostream>
#include <fstream>

int main()
{
    std::ofstream inputFile("../Matrix/INPUT.TXT");
    if (!inputFile.is_open())
    {
        std::cout << "Не удалось открыть" << std::endl;
        return 1;
    }

    int N;
    std::cout << "Введите N: ";
    std::cin >> N;
    inputFile << N << std::endl;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile << i << " ";
        }
        inputFile << std::endl;
    }
    
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile << j << " ";
        }
        inputFile << std::endl;
    }
    return 0;
}
