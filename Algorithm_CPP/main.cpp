#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void IOFaster() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

int dr[] = { 0,1,0,-1 };
int dc[] = { 1,0,-1,0 };

void findBlock(int row, int col, vector<vector<bool>> &visit, vector<vector<int>> &table, vector<int> &block) {
	visit[row][col] = true;

	for (int i = 0; i < 4; i++) {
		int newRow = row + dr[i];
		int newCol = col + dc[i];

		if (newRow < 0 || newCol < 0 || newRow >= table.size() || newCol >= table[0].size())
			continue;

		if (table[newRow][newCol] && !visit[newRow][newCol]) {
			block.push_back(i);
			findBlock(newRow, newCol, visit, table, block);
		}
	}
}

bool isSame(vector<int> &block, vector<vector<int>> &blocks, vector<int> &isUsed) {
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].size() == block.size() && !isUsed[i]) {
			if (blocks[i].size() == 1) {
				isUsed[i] = true;
				return true;
			}

			for (int j = 0; j < 4; j++) {
				bool result = true;
				for (int k = 1; k < block.size(); k++) {
					int dir = blocks[i][k] + j;
					if (dir > 3)
						dir -= 4;

					if (dir != block[k]) {
						result = false;
						break;
					}
				}
				if (result) {
					isUsed[i] = true;
					return true;
				}
			}
		}
	}

	return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
	int answer = -1;

	vector<vector<int>> blocks;
	vector<vector<bool>> visit(table.size(), vector<bool>(table[0].size()));

	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j] && !visit[i][j]) {
				vector<int> block;
				block.push_back(-1);
				findBlock(i, j, visit, table, block);
				blocks.push_back(block);
			}
		}
	}

	for (int i = 0; i < game_board.size(); i++) {
		for (int j = 0; j < game_board[i].size(); j++) {
			game_board[i][j] = !game_board[i][j];
		}
	}

	vector<vector<bool>> visitBoard(game_board.size(), vector<bool>(game_board[0].size()));
	vector<int> isUsed(blocks.size());
	for (int i = 0; i < game_board.size(); i++) {
		for (int j = 0; j < game_board[i].size(); j++) {
			if (game_board[i][j] && !visitBoard[i][j]) {
				vector<int> block;
				block.push_back(-1);
				findBlock(i, j, visitBoard, game_board, block);
				
				bool result = isSame(block, blocks, isUsed);
				if (result) {
					answer += block.size();
				}
			}
		}
	}

	return answer;
}

int main() {
	IOFaster();

	int N;
	cin >> N;


	return 0;
}