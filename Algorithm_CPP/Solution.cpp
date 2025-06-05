#include "solution.h"

bool Solution::solution_250507_01(string s)
{
	int count = 0;

	for (int i = 0; i < s.size(); i++) {
		if (s.at(i) == '(') {
			count++;
		}
		else {
			if (count < 1)
				return false;
			count--;
		}
	}

	if (count != 0)
		return false;

	return true;
}

int Solution::solution_250507_02(vector<int> numbers, int target)
{
	int answer = 0;

	queue<pair<int, int>> bfs;
	bfs.push({ 1, numbers.at(0) });
	bfs.push({ 1, numbers.at(0) * -1 });

	while (!bfs.empty()) {
		pair<int, int> temp = bfs.front();
		bfs.pop();

		int idx = temp.first;

		if (temp.first >= numbers.size()) {
			if (temp.second == target)
				answer++;

			continue;
		}

		bfs.push({ idx + 1 , temp.second + numbers.at(idx) });
		bfs.push({ idx + 1 , temp.second - numbers.at(idx) });
	}

	return answer;
}

string Solution::solution_250528_01(vector<int> numbers)
{
	string answer = "";

	vector<string> strs;
	for (int num : numbers) {
		strs.push_back(to_string(num));
	}

	sort(strs.begin(), strs.end(), [](const string &a, const string &b) {
		return a + b > b + a;
	});

	if (!strs.empty() && strs[0] == "0") {
		return "0";
	}

	for (string &s : strs) {
		answer += s;
	}

	return answer;
}

int Solution::solution_250529_01(vector<vector<int>> maps)
{
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
	bfs.push(GameMap(0, 0, 1));

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

void dfs_250530_01(int &node, vector<vector<int>> &computers, vector<bool> &visit) {
	if (visit[node])
		return;

	visit[node] = true;
	for (int i = 0; i < computers[node].size(); i++) {
		if (!visit[i] && computers[node][i])
			dfs_250530_01(i, computers, visit);
	}
}

int Solution::solution_250530_01(int n, vector<vector<int>> computers)
{
	int answer = 0;
	vector<bool> visit(n);
	for (int i = 0; i < visit.size(); i++) {
		if (!visit[i]) {
			dfs_250530_01(i, computers, visit);
			answer++;
		}
	}

	return answer;
}

int Solution::solution_250602_01(string begin, string target, vector<string> words)
{
	unordered_map<string, int> visit;
	for (string word : words) {
		visit[word] = 0;
	}

	queue<pair<string, int>> bfs;
	bfs.push({ begin, 0 });

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

int Solution::solution_250523_01()
{
	// Two Pointer

	IOFaster();
	long N, temp, goodVal = 0;
	vector<long> vec;

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> temp;
		vec.push_back(temp);
	}

	if (N <= 2) {
		cout << goodVal << endl;
		return 0;
	}

	sort(vec.begin(), vec.end());
	for (int i = 0; i < N; i++) {
		long val = vec[i];
		int left = 0;
		int right = vec.size() - 1;

		while (left < right) {
			long result = vec[left] + vec[right];
			if (left == i) {
				left++;
				continue;
			}
			if (right == i) {
				right--;
				continue;
			}

			if (result == val) {
				goodVal++;
				break;
			}
			else if (result < val) {
				left++;
			}
			else {
				right--;
			}
		}
	}

	cout << goodVal << endl;

	return 0;
}

int Solution::solution_250604_01()
{
	IOFaster();

	int N;
	cin >> N;

	vector<pair<int, int>> A(N);

	for (int i = 0; i < N; ++i) {
		int temp;
		cin >> temp;
		A[i] = { temp, i };
	}

	sort(A.begin(), A.end());

	int max = 0;
	for (int i = 0; i < N; ++i) {
		int index = A[i].second - i;
		if (max < index)
			max = index;
	}

	cout << max + 1 << endl;

	return 0;
}

bool isPrime_250605(int num) {
	if (num == 2)
		return true;

	for (int i = 2; i < num; i++)
		if (num % i == 0)
			return false;

	return true;
}

void dfs_250605(int value, int index, int N) {
	if (!isPrime_250605(value))
		return;

	if (index == N) {
		cout << value << "\n";
		return;
	}

	for (int i = 0; i <= 9; i++) {
		int temp = value * 10 + i;
		dfs_250605(temp, index + 1, N);
	}
}

int Solution::solution_250605_01()
{
	IOFaster();

	int N;
	cin >> N;

	int prime[] = { 2,3,5,7 };

	for (int i = 0; i < 4; i++)
		dfs_250605(prime[i], 1, N);

	return 0;
}
