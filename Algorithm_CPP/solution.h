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
	bool	solution_250507_01(string s);											// 올바른 괄호
	int		solution_250507_02(vector<int> numbers, int target);					// 타겟 넘버
	string	solution_250528_01(vector<int> numbers);								// 가장 큰 수
	int		solution_250529_01(vector<vector<int> > maps);							// 게임 맵 최단 거리 (bfs)
	int		solution_250530_01(int n, vector<vector<int>> computers);				// 네트워크 (dfs)
	int		solution_250602_01(string begin, string target, vector<string> words);	// 단어 변환 (bfs)
	int		solution_250610_01(vector<int> citations);								// H-Index

	// Baekjoon
	int		solution_250523_01();													// No.1253 좋다
	int		solution_250604_01();													// No.1377 버블 소트
	int		solution_250605_01();													// No.2023 신기한 소수
	int		solution_250607_01();													// No.13023 ABCDE
	int		solution_250608_01();													// No.1167 트리의 지름
	int		solution_250609_01();													// No.1931 회의실 배정
};