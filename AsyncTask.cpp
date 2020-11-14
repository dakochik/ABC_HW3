#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

std::pair<int, int> countIndexes(std::vector<long> array)
{
	std::pair<int, int> res;
	long long highestScore = NULL;
#pragma omp parallel for
	for (int i = 0; i < array.size(); i++)
	{
		for (int y = i + 1; y < array.size(); ++y)
		{
			long long sum = array[i];
			for (int j = i + 1; j <= y; ++j)
			{
				sum += static_cast<long long>(array[j]) * static_cast<long long>(pow(-1, j - i));
			}
#pragma omp critical
			if ((highestScore == NULL) || (sum > highestScore))
			{
				res = std::pair<int, int>(i, y);
				highestScore = sum;
			}
		}
	}
	return res;
}

int main(int argc, char* argv[])
{
	std::string vecStr;
	std::vector<long> vect;
	long val;

	std::ifstream in;
	in.open(argv[1]);
	while (std::getline(in, vecStr))
	{
		vect.push_back(std::stol(vecStr));
	}
	in.close();

	std::pair<int, int> result = countIndexes(vect);

	std::ofstream out;
	out.open(argv[2]);
	out << result.first << std::endl;
	out << result.second << std::endl;
	out.close();
}
