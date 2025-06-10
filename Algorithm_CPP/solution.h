#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
	void IOFaster() {
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}

	// Programmers
	bool	solution_250507_01(string s);											// �ùٸ� ��ȣ
	int		solution_250507_02(vector<int> numbers, int target);					// Ÿ�� �ѹ�
	string	solution_250528_01(vector<int> numbers);								// ���� ū ��
	int		solution_250529_01(vector<vector<int> > maps);							// ���� �� �ִ� �Ÿ� (bfs)
	int		solution_250530_01(int n, vector<vector<int>> computers);				// ��Ʈ��ũ (dfs)
	int		solution_250602_01(string begin, string target, vector<string> words);	// �ܾ� ��ȯ (bfs)
	int		solution_250610_01(vector<int> citations);								// H-Index

	// Baekjoon
	int		solution_250523_01();													// No.1253 ����
	int		solution_250604_01();													// No.1377 ���� ��Ʈ
	int		solution_250605_01();													// No.2023 �ű��� �Ҽ�
	int		solution_250607_01();													// No.13023 ABCDE
	int		solution_250608_01();													// No.1167 Ʈ���� ����
	int		solution_250609_01();													// No.1931 ȸ�ǽ� ����
};