#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;


class GameMap {
public:
	int row;
	int col;
	int count;

	GameMap(int row, int col, int count) {
		this->row = row;
		this->col = col;
		this->count = count;
	}
};

int solution(vector<vector<int> > maps)
{
	vector<vector<bool>> visit(maps.size());
	for (int i = 0; i < maps.size(); i++) {
		vector<bool> temp;
		for (int j = 0; j < maps[i].size(); j++) {
			temp.push_back(false);
		}
		visit[i] = temp;
	}

	if (maps[0][0] == 0)
		return -1;

	queue<GameMap> bfs;
	bfs.push(GameMap(0,0,1));

	int dr[] = { 0,0,1,-1 };
	int dc[] = { 1, -1, 0,0 };

	while (!bfs.empty()) {
		GameMap temp = bfs.front();
		bfs.pop();

		if (visit[temp.row][temp.col] || !maps[temp.row][temp.col])
			continue;

		if (temp.row == maps.size() - 1 && temp.col == maps[0].size() - 1)
			return temp.count;

		visit[temp.row][temp.col] = true;

		for (int i = 0; i < 4; i++) {
			int nextRow = temp.row + dr[i];
			int nextCol = temp.col + dc[i];

			if (nextRow < 0 || nextRow >= maps.size() || nextCol < 0 || nextCol >= maps[0].size())
				continue;
			
			if (visit[nextRow][nextCol] || !maps[nextRow][nextCol])
				continue;

			bfs.push(GameMap(nextRow, nextCol, temp.count + 1));
		}

	}

	return -1;
}

void IOFaster() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

int main() {

	IOFaster();

	return 0;
}
