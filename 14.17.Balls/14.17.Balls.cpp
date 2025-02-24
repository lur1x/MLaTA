/*
14.17. Шары (5)
По горизонтально расположенному желобу бесконечной длины катятся с одинаковой скоростью N металлических шаров (1 ≤ N ≤ 106). Некоторые шары катятся вправо, некоторые влево. Сталкиваясь, шары испытывают абсолютно упругое соударение (то есть меняют направление движения, сохраняя скорость). Зная расположение шаров в желобе  и направление их движения, сосчитать количество столкновений (соударений) пар шаров.
Ввод. Входной файл INPUT.TXT содержит одну строку. В ней символами «>» и «<» указаны направления движения шаров.
Вывод. В единственной строке файла OUTPUT.TXT требуется вывести число соударений.
Ограничение. Затраты оперативной памяти не должны превышать 1 Мгб.
Примеры
Ввод 1        Ввод 2
7             5
>><>>><       <<<>>
Вывод 1       Вывод 2
7   
0
ФИО: Кириллов Дмитрий Геннадьевич
Группа: ПС-22
Среда разработки: Visual Studio 22
*/

#include <iostream>
#include <fstream>
#include <string>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

Args ParseArgs(int argc, char** argv)
{
    if (argc != 3)
    {
        throw std::runtime_error("Invalid arguments count \n Usage: balls.exe <input file> <output file>");
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    return args;
}

unsigned int CountСollisions(std::ifstream& input)
{
    
    unsigned int collisions = 0;  
    unsigned int right_count = 0; 
    char ch;

    while (input.get(ch))
    {
		if (ch == '>')
		{
			right_count++;
		}
		else if (ch == '<')
		{
			collisions += right_count;
		}
		
    }

	if (input.bad() || !input.eof())
	{
		throw std::runtime_error("Error reading input file");
	}

    return collisions;
}


void CountСollisionsInFile(const std::string& inputFilePath, const std::string& outputFilePath)
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
	
	unsigned int collisions = CountСollisions(inputFile);
	outputFile << collisions;
	
}

int main(int argc, char* argv[]) {

    try 
	{
        auto args = ParseArgs(argc, argv);
		CountСollisionsInFile(args.inputFileName, args.outputFileName);
    }

    catch(const std::exception& e) 
	{
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}