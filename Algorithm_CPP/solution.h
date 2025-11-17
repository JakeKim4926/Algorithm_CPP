#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
	bool	solution_250507_01(string s);													// 올바른 괄호
	int		solution_250507_02(vector<int> numbers, int target);							// 타겟 넘버
	string	solution_250528_01(vector<int> numbers);										// 가장 큰 수
	int		solution_250529_01(vector<vector<int> > maps);									// 게임 맵 최단 거리 (bfs)
	int		solution_250530_01(int n, vector<vector<int>> computers);						// 네트워크 (dfs)
	int		solution_250602_01(string begin, string target, vector<string> words);			// 단어 변환 (bfs)
	int		solution_250610_01(vector<int> citations);										// H-Index
	int		solution_250611_01(int n, vector<vector<int>> costs);							// 섬 연결하기
	int		solution_250612_01(vector<vector<int>> game_board, vector<vector<int>> table);	// 퍼즐 조각 채우기
	int		solution_250613_01(int n, vector<vector<int>> wires);							// 전력 망을 둘로 나누기

	// Baekjoon
	int		solution_250523_01();															// No.1253 좋다
	int		solution_250604_01();															// No.1377 버블 소트
	int		solution_250605_01();															// No.2023 신기한 소수
	int		solution_250607_01();															// No.13023 ABCDE
	int		solution_250608_01();															// No.1167 트리의 지름
	int		solution_250609_01();															// No.1931 회의실 배정
	int		solution_250616_01();															// No.7576 토마토 
	int		solution_251111_01();															// No.2563 색종이
	int		solution_251112_01();															// No.17413 단어 뒤집기 2
	int		solution_251113_01();															// No.2607 비슷한 단어
	int		solution_251114_01();															// No.2293 동전 1
	int		solution_251115_01();															// No.15654 N과 M(5)
	int		solution_251116_01();															// No.17478 재귀함수가 뭔가요?
	int		solution_251117_01();															// No.23304 아카라카
};