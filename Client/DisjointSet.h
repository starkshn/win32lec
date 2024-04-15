#pragma once
class DisjointSet
{
public:
	DisjointSet(int num) : _parent(num), _rank(num, 1)
	{
		for (int i = 0; i < num; ++i)
		{
			_parent[i] = i;
		}
	}

public:
	int FindParent(int u)
	{
		if (u == _parent[u]) return u;
		return _parent[u] = FindParent(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = FindParent(u);
		v = FindParent(v);

		if (u == v) return;

		if (_rank[u] > _rank[v]) swap(u, v);

		_parent[u] = v;
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

