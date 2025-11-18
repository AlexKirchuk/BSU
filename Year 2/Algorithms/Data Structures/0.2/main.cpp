#include <fstream>
#include <vector>

int main()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	int n;
	in >> n;

	std::vector<int> heap(n);
	for (int i = 0; i < n; i++)
	{
		in >> heap[i];
	}

	bool isHeap = true;
	for (int i = 0; 2 * i + 1 < n; i++)
	{
		if ((2 * i + 1 < n && heap[i] > heap[2 * i + 1]) ||
			(2 * i + 2 < n && heap[i] > heap[2 * i + 2]))
		{
			isHeap = false;
			break;
		}
	}

	if (isHeap)
	{
		out << "Yes";
	}
	else
	{
		out << "No";
	}
	return 0;
}