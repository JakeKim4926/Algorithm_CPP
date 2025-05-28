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
