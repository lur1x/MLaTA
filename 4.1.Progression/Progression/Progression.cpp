#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("INPUT.TXT");
	ofstream fout("OUTPUT.TXT");

	int N, M;
	fin >> N >> M;

	vector<int> X(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> X[i];
	}

	int K = N;
	vector<int> progression;

	// Проверяем все возможные подпоследовательности длины M
	for (int i = 0; i <= N - M; ++i)
	{
		for (int j = i + 1; j <= N - M + 1; ++j)
		{
			bool isProgression = true;
			int d = X[j] - X[i];
			if (d != 13)
				continue; // Нас интересует только разность 13

			// Проверяем, что следующие M-2 элементов образуют прогрессию с разностью d
			for (int k = 2; k < M; ++k)
			{
				if (i + k >= N || X[i + k] != X[i] + k * d)
				{
					isProgression = false;
					break;
				}
			}

			if (isProgression)
			{
				// Найдена несчастливая прогрессия
				if (i + M - 1 < K)
				{
					K = i + M - 1;
					progression.clear();
					for (int k = 0; k < M; ++k)
					{
						progression.push_back(X[i + k]);
					}
				}
			}
		}
	}

	if (progression.empty())
	{
		fout << N << "\nNo\n";
	}
	else
	{
		fout << K << "\n";
		for (int i = 0; i < progression.size(); ++i)
		{
			if (i > 0)
				fout << " ";
			fout << progression[i];
		}
		fout << "\n";
	}

	fin.close();
	fout.close();
	return 0;
}