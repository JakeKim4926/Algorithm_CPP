#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

void dfs(int &node, vector<vector<int>> &computers, vector<bool> &visit) {
	if (visit[node])
		return;

	visit[node] = true;
	for (int i = 0; i < computers[node].size(); i++) {
		if (!visit[i] && computers[node][i])
			dfs(i, computers, visit);
	}
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	vector<bool> visit(n);
	for (int i = 0; i < visit.size(); i++) {
		if (!visit[i]) {
			dfs(i, computers, visit);
			answer++;
		}
	}

	return answer;
}

void IOFaster() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

int main() {

	IOFaster();

	return 0;
}
