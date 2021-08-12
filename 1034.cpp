#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#pragma warning(disable:4996)
using namespace std;

bool cmp(pair<string, int>a, pair<string, int>b)
{
	return a.second > b.second;
}

int main()
{
	int var1 = 0;
	int var2 = 0;
	scanf("%d %d", &var1, &var2);
	string var3;
	var3.resize(3);
	string var4;
	var4.resize(3);
	
	unordered_map<string, int> time;
	unordered_map<string, int> parent;
	vector<vector<string>> group;
	group.resize(var1);

	for (int i = 0; i < var1; i++)
	{
		string var3;
		var3.resize(3);
		string var4;
		var4.resize(3);
		int var5 = 0;
		scanf("%s %s %d", &var3[0], &var4[0], &var5);
		time[var3] += var5;
		time[var4] += var5;
		group[i].emplace_back(var3);
		group[i].emplace_back(var4);
		if (parent.find(var3) == parent.end())
		{
			parent[var3] = i;
		}
		if (parent.find(var4) == parent.end())
		{
			parent[var4] = i;
		}
	}
	for (int i = 0; i < group.size(); i++)
	{
		if (parent[group[i][0]] > parent[group[i][1]])
		{
			parent[group[i][0]] = parent[group[i][1]];
		}
		else
		{
			parent[group[i][1]] = parent[group[i][0]];
		}
	}

	unordered_map<int, int>total_time;
	unordered_map<int, int>total_count;
	unordered_map<int, int>flag;
	int print_count = 0;
	vector<pair<string, int>>head;
	
	for (auto it = time.begin(); it != time.end(); it++)
	{
		head.emplace_back(pair<string, int>(it->first.c_str(), it->second));
		total_time[parent[it->first.c_str()]] += it->second;
		total_count[parent[it->first.c_str()]] += 1;
		if (flag[parent[it->first.c_str()]] != 1 && total_time[parent[it->first.c_str()]] > var2 * 2 && total_count[parent[it->first.c_str()]] >= 3)
		{
			flag[parent[it->first.c_str()]] = 1;
			print_count++;
		}
		else
		{
			flag[parent[it->first.c_str()]] = 0;
		}
	}

	sort(head.begin(), head.end(), cmp);
	printf("%d", print_count);
	for (int i = 0; print_count > 0; i++)
	{
		if (flag[parent[head[i].first.c_str()]] == 1)
		{
			printf("\n%s %d", head[i].first.c_str(), total_count[parent[head[i].first.c_str()]]);
			flag[parent[head[i].first.c_str()]] = 0;
			print_count--;
		}
	}
	return 0;
}