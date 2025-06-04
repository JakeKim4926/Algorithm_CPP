#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void IOFaster() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

int main() {
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