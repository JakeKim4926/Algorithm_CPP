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
	bool	solution_250507_01(string s);								// 올바른 괄호
	int		solution_250507_02(vector<int> numbers, int target);		// 타겟 넘버
	string	solution_250528_01(vector<int> numbers);					// 가장 큰 수
	int		solution_250529_01(vector<vector<int> > maps);				// 게임 맵 최단 거리 (bfs)
	int		solution_250530_01(int n, vector<vector<int>> computers);	// 네트워크 (dfs)

	// Baekjoon
	int		solution_250523_01();										// No.1253 좋다
};