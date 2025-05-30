#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	void IOFaster() {
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
	}

	// Programmers
	bool	solution_250507_01(string s);								// �ùٸ� ��ȣ
	int		solution_250507_02(vector<int> numbers, int target);		// Ÿ�� �ѹ�
	string	solution_250528_01(vector<int> numbers);					// ���� ū ��
	int		solution_250529_01(vector<vector<int> > maps);				// ���� �� �ִ� �Ÿ� (bfs)
	int		solution_250530_01(int n, vector<vector<int>> computers);	// ��Ʈ��ũ (dfs)

	// Baekjoon
	int		solution_250523_01();										// No.1253 ����
};