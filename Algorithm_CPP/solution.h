#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <set>
#include <stack>

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
	int		solution_250523_01();															// [G4] No.1253 좋다
	int		solution_250604_01();															// [G2] No.1377 버블 소트
	int		solution_250605_01();															// [G5] No.2023 신기한 소수
	int		solution_250607_01();															// [G5] No.13023 ABCDE
	int		solution_250608_01();															// [G2] No.1167 트리의 지름
	int		solution_250609_01();															// [G5] No.1931 회의실 배정
	int		solution_250616_01();															// [G5] No.7576 토마토 
	int		solution_251111_01();															// [S5] No.2563 색종이
	int		solution_251112_01();															// [S3] No.17413 단어 뒤집기 2
	int		solution_251113_01();															// [S2] No.2607 비슷한 단어
	int		solution_251114_01();															// [G5] No.2293 동전 1
	int		solution_251115_01();															// [S3] No.15654 N과 M(5)
	int		solution_251116_01();															// [S5] No.17478 재귀함수가 뭔가요?
	int		solution_251117_01();															// [S2] No.23304 아카라카
	int		solution_251118_01();															// [G5] No.7569 토마토
	int		solution_251119_01();															// [G4] No.9935 문자열 폭발
	int		solution_251120_01();															// [G5] No.12865 평범한 배낭
	int		solution_251121_01();															// [G5] No.9205 맥주 마시면서 걸어가기
	int		solution_251122_01();															// [S5] No.4673 셀프 넘버
	int		solution_251123_01();															// [S1] No.16918 봄버맨
	int		solution_251124_01();															// [G5] No.18869 멀티버스 2
	int		solution_251125_01();															// [G5] No.2212 센서
	int		solution_251126_01();															// [G4] No.5052 전화번호 목록
	int		solution_251127_01();															// [G5] No.15591 MooTube (Silver)
	int		solution_251128_01();															// [G4] No.1976 여행 가자
	int		solution_251129_01();															// [G5] No.18428 감시 피하기
	int		solution_251201_01();															// [G5] No.2166 다각형의 면적
	int		solution_251202_01();															// [G5] No.12919 A와 B 2
	int		solution_251203_01();															// [S1] No.9465 스티커
	int		solution_251204_01();															// [G5] No.14503 로봇 청소기
	int		solution_251205_01();															// [G5] No.20437 문자열 게임 2
	int		solution_251208_01();															// [G5] No.2668 숫자고르기
	int		solution_251209_01();															// [G5] No.14719 빗물
	int		solution_251210_01();															// [G5] No.5972 택배 배송
	int		solution_251211_01();															// [G5] No.22251 빌런 호석
	int		solution_251212_01();															// [G5] No.7490 0 만들기
	int		solution_251213_01();															// [G4] No.4485 녹색 옷 입은 애가 젤다지?
	int		solution_251214_01();															// [G4] No.16234 인구 이동
	int		solution_251215_01();															// [G4] No.1027 고층 건물
	int		solution_251216_01();															// [G4] No.2138 전구와 스위치
	int		solution_251217_01();															// [G4] No.2631 줄 세우기
	int		solution_251218_01();															// [G2] No.12015 가장 긴 증가하는 부분 수열2
	int		solution_251219_01();															// [G2] No.12014 주식
	int		solution_251220_01();															// [P5] No.13711 LCS 4
	int		solution_251222_01();															// [G2] No.1818 책정리
	int		solution_251223_01();															// [G4] No.1863 스카이라인 쉬운거
	int		solution_251225_01();															// [G2] No.12738 가장 긴 증가하는 부분 수열3
	int		solution_251227_01();															// [G1] No.9702 LIS
	int		solution_260101_01();															// [G4] No.2179 비슷한 단어
	int		solution_260105_01();															// [G5] No.10026 적록색약
};