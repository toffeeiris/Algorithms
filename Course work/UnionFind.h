const int MAX_SIZE = 50;

class UnionFind
{
	int parents[MAX_SIZE];
	int ranks[MAX_SIZE];
public:

	UnionFind(int);
	int Find(int);
	bool Union(int, int);

};

UnionFind::UnionFind(int size)
{
	for (int x = 0; x < size; x++)
	{
		parents[x] = x;
		ranks[x] = 0;
	}
}

int UnionFind::Find(int x)
{
	int root = x;
	while (parents[root] != root)
		root = parents[root];

	int i = x;
	while (parents[i] != i)
	{
		int j = parents[i];
		parents[i] = root;
		i = j;
	}
	return root;
}

bool UnionFind::Union(int x, int y)
{
	x = Find(x);
	y = Find(y);

	if (x == y)
		return false;

	if (ranks[x] == ranks[y])
	{
		parents[y] = x;
		ranks[x]++;
	}
	else if (ranks[x] < ranks[y])
		parents[x] = y;
	else if (ranks[x] > ranks[y])
		parents[y] = x;

	return true;
}