#pragma once

#include <vector>

class FenwickTree
{
public:
	FenwickTree(int size)
		: tree(size + 1, 0)
	{
	}

	void Update(int index, int delta);

	int Query(int index) const;

	int FindPosition(int target) const;

private:
	std::vector<int> tree;
};
