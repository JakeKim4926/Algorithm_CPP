#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> numbers, int target) {
	int answer = 0;

	queue<pair<int,int>> bfs;
	bfs.push({ 0, numbers.at(0) });
	bfs.push({ 0, numbers.at(0) * -1 });

	while (!bfs.empty()) {
		pair<int, int> temp = bfs.front();
		bfs.pop();

		if (temp.second == target)
			answer++;
		if (temp.first >= numbers.size())
			continue;

		bfs.push({ temp.first + 1 , temp.second + numbers.at(temp.first)});
		bfs.push({ temp.first + 1 , temp.second - numbers.at(temp.first)});
	}

	cout << answer << endl;

	return answer;
}

int main() {


	return 0;
}