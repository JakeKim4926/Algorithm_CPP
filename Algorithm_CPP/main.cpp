#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int solution(string begin, string target, vector<string> words) {
	
	unordered_map<string, int> visit;
	for (string word : words) {
		visit[word] = 0;
	}

	queue<pair<string, int>> bfs;
	bfs.push({ begin, 0});

	while (!bfs.empty()) {
		string temp = bfs.front().first;
		int count = bfs.front().second;
		bfs.pop();

		if (visit[temp])
			continue;

		if (temp == target)
			return count;

		visit[temp] = 1;
		for (int i = 0; i < temp.length(); i++) {
			char alphabet = 'a';
			string newWord = temp;
			for (int j = 0; j < 26; j++) {
				newWord[i] = alphabet + j;

				if (visit[newWord])
					continue;
				
				for (int k = 0; k < words.size(); k++) {
					if (words[k] == newWord)
						bfs.push({ newWord, count + 1 });
				}
			}
		}
	}

	return 0;
}

void IOFaster() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

int main() {

	IOFaster();

	return 0;
}
