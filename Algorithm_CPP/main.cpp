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

void dfs(int index, int& count, vector<bool> &visit, vector<vector<int>> &vecNodes) {
	visit[index] = true;
	count++;

	for (int i = 0; i < vecNodes[index].size(); i++) {
		int next = vecNodes[index][i];
		if(!visit[next]) {
			dfs(next, count, visit, vecNodes);
		}
	}
}

int solution(int n, vector<vector<int>> wires) {
	int answer = INT_MAX;

	vector<vector<int>> vecNodes(n+1);

	for (auto vec : wires) {
		int from = vec[0];
		int to = vec[1];

		vecNodes[from].push_back(to);
		vecNodes[to].push_back(from);
	}

	for (int i = 1; i < vecNodes.size(); i++) {
		for (int j = 0; j < vecNodes[i].size(); j++) {
			vector<bool> visit(n + 1);

			int from = i;
			int to = vecNodes[i][j];

			visit[to]= true;
			
			int count = 0;
			dfs(from, count, visit, vecNodes);

			int elseSize = n - count;
			int diff = abs(elseSize - count);
			if (answer > diff)
				answer = diff;
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