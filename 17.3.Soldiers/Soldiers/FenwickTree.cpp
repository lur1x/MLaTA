#include "FenwickTree.h"

void FenwickTree::Update(int index, int delta)
{
	for (; index < tree.size(); index += index & -index)
	{
		tree[index] += delta;
	}
}

int FenwickTree::Query(int index) const
{
	int res = 0;
	for (; index > 0; index -= index & -index)
	{
		res += tree[index];
	}
	return res;
}

int FenwickTree::FindPosition(int target) const
{
	int left = 1, right = tree.size() - 1;
	int pos = 0;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		int sum = Query(mid);
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