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

int Solution::solution_250610_01(vector<int> citations)
{
	int answer = 0;
	sort(citations.begin(), citations.end(), greater<int>());

	for (int i = 0; i < citations.size(); i++) {
		if (citations[i] >= i + 1) {
			answer = i + 1;
		}
		else {
			break;
		}
	}

	return answer;
}

int Solution::solution_250611_01(int n, vector<vector<int>> costs)
{
	vector<vector<pair<int, int>>> graph(n);

	for (const auto& edge : costs) {
		int from = edge[0];
		int to = edge[1];
		int cost = edge[2];
		graph[from].push_back({ to, cost });
		graph[to].push_back({ from, cost });
	}

	vector<bool> visited(n, false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, 0 });

	int totalCost = 0;

	while (!pq.empty()) {
		pair<int, int> top = pq.top(); 
		pq.pop();

		int cost = top.first;
		int node = top.second;

		if (visited[node]) continue;

		visited[node] = true;
		totalCost += cost;

		for (const auto& edge : graph[node]) {
			int next = edge.first;
			int nextCost = edge.second;

			if (!visited[next]) {
				pq.push({ nextCost, next });
			}
		}
	}

	return totalCost;
}

typedef pair<int, int> Coord;
typedef vector<Coord> Shape;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

void normalize(Shape &shape) {
	int minRow = shape[0].first, minCol = shape[0].second;
	for (int i = 1; i < shape.size(); i++) {
		minRow = min(minRow, shape[i].first);
		minCol = min(minCol, shape[i].second);
	}
	for (int i = 0; i < shape.size(); i++) {
		shape[i].first -= minRow;
		shape[i].second -= minCol;
	}
	sort(shape.begin(), shape.end());
}

Shape extractShape(int sr, int sc, vector<vector<int>> &board, int target) {
	int n = board.size();
	queue<Coord> q;
	Shape shape;
	q.push({ sr, sc });
	board[sr][sc] = -1;
	shape.push_back({ 0, 0 });

	while (!q.empty()) {
		Coord cur = q.front(); q.pop();
		int r = cur.first, c = cur.second;

		for (int d = 0; d < 4; ++d) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (nr >= 0 && nc >= 0 && nr < n && nc < n && board[nr][nc] == target) {
				board[nr][nc] = -1;
				q.push({ nr, nc });
				shape.push_back({ nr - sr, nc - sc });
			}
		}
	}

	normalize(shape);
	return shape;
}

Shape rotate90(const Shape &shape) {
	Shape rotated;
	for (int i = 0; i < shape.size(); i++) {
		int r = shape[i].first;
		int c = shape[i].second;
		rotated.push_back({ c, -r });
	}
	normalize(rotated);
	return rotated;
}

bool isMatch(const Shape &hole, Shape block) {
	for (int i = 0; i < 4; i++) {
		if (hole == block)
			return true;
		block = rotate90(block);
	}
	return false;
}

int Solution::solution_250612_01(vector<vector<int>> game_board, vector<vector<int>> table)
{
	int n = game_board.size();
	vector<Shape> blocks;
	vector<Shape> holes;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (table[i][j] == 1)
				blocks.push_back(extractShape(i, j, table, 1));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (game_board[i][j] == 0)
				holes.push_back(extractShape(i, j, game_board, 0));

	int answer = 0;
	vector<bool> used(blocks.size(), false);

	for (int i = 0; i < holes.size(); i++) {
		for (int j = 0; j < blocks.size(); j++) {
			if (used[j]) continue;
			if (isMatch(holes[i], blocks[j])) {
				answer += blocks[j].size();
				used[j] = true;
				break;
			}
		}
	}

	return answer;
}

void dfs_250613(int index, int& count, vector<bool> &visit, vector<vector<int>> &vecNodes) {
	visit[index] = true;
	count++;

	for (int i = 0; i < vecNodes[index].size(); i++) {
		int next = vecNodes[index][i];
		if (!visit[next]) {
			dfs_250613(next, count, visit, vecNodes);
		}
	}
}

int Solution::solution_250613_01(int n, vector<vector<int>> wires)
{
	int answer = INT_MAX;

	vector<vector<int>> vecNodes(n + 1);

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

			visit[to] = true;

			int count = 0;
			dfs_250613(from, count, visit, vecNodes);

			int elseSize = n - count;
			int diff = abs(elseSize - count);
			if (answer > diff)
				answer = diff;
		}
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

bool friendship(int node, int index, vector<bool> &visit, vector<vector<int>> &friends) {
	if (index == 4)
		return true;

	visit[node] = true;
	for (int i = 0; i < friends[node].size(); i++) {
		int next = friends[node][i];
		if (!visit[next]) {
			visit[next] = true;
			bool result = friendship(next, index + 1, visit, friends);
			visit[next] = false;

			if (result)
				return true;
		}
	}
	return false;
}

int Solution::solution_250607_01()
{
	IOFaster();

	int node, edge = 0;
	bool result = false;
	cin >> node >> edge;

	vector<vector<int>> friends(node, vector<int>(0));

	for (int i = 0; i < edge; i++) {
		int to, from = 0;
		cin >> to >> from;
		friends[to].push_back(from);
		friends[from].push_back(to);
	}

	for (int i = 0; i < node; i++) {
		vector<bool> visit(node, false);
		result = friendship(i, 0, visit, friends);
		if (result)
			break;
	}

	if (result)	cout << 1 << "\n";
	else		cout << 0 << "\n";

	return 0;
}

class Node {
public:
	int next;
	int distance;

	Node() {  };

	Node(int next, int distance) {
		this->next = next;
		this->distance = distance;
	}
};

void bfs_250608(int &index, int &max, vector<vector<Node>> &tree) {
	vector<bool> visit(tree.size());
	visit[index] = true;

	vector<int> vecDistance(tree.size());

	queue<Node> bfs;
	for (int i = 0; i < tree[index].size(); i++)
		bfs.push(Node(tree[index][i].next, tree[index][i].distance));

	while (!bfs.empty()) {
		Node temp = bfs.front();
		bfs.pop();

		vecDistance[temp.next] = temp.distance;

		visit[temp.next] = true;
		for (int i = 0; i < tree[temp.next].size(); i++) {
			int next = tree[temp.next][i].next;
			int distance = tree[temp.next][i].distance;
			if (!visit[next]) {
				bfs.push(Node(next, temp.distance + distance));
			}
		}
	}

	for (int i = 1; i < tree.size(); i++) {
		if (max < vecDistance[i]) {
			max = vecDistance[i];
			index = i;
		}
	}
}

int Solution::solution_250608_01()
{
	IOFaster();

	int V;
	cin >> V;

	vector<vector<Node>> tree(V + 1, vector<Node>(0));

	int temp = 1;
	while (temp <= V) {
		int node, next, distance = 0;
		cin >> node;

		while (1) {
			cin >> next;
			if (next == -1)
				break;

			cin >> distance;

			tree[node].push_back(Node(next, distance));
		}
		temp++;
	}

	int max = 0, index = 1;
	bfs_250608(index, max, tree);
	bfs_250608(index, max, tree);

	cout << max << "\n";

	return 0;
}

bool compare_250609(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}

	return a.second < b.second;
}


int Solution::solution_250609_01()
{
	IOFaster();

	int N;
	cin >> N;
	vector<pair<int, int>> vecMeeting;
	for (int i = 0; i < N; i++) {
		int start, end = 0;
		cin >> start >> end;
		vecMeeting.push_back({ start, end });
	}

	int result = 1;

	sort(vecMeeting.begin(), vecMeeting.end(), compare_250609);

	int end = vecMeeting[0].second;
	int index = 1;
	while (index < N) {
		if (vecMeeting[index].first < end) {
			index++;
			continue;
		}

		end = vecMeeting[index++].second;
		result++;
	}

	cout << result << "\n";

	return 0;
}

int Solution::solution_250616_01()
{
	struct Tomato {
		int row;
		int col;
		int count;

		Tomato(int row, int col, int count) {
			this->row = row;
			this->col = col;
			this->count = count;
		}
	};

	IOFaster();

	int row, col, count = 0;
	cin >> col >> row;
	vector<vector<int>> farm(row);
	queue<Tomato> bfs;

	bool isDone = true;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int temp = 0;
			cin >> temp;
			farm[i].push_back(temp);

			if (temp)
				bfs.push(Tomato(i, j, 0));
			else if (!temp && isDone)
				isDone = false;
		}
	}

	if (isDone) {
		cout << 0 << "\n";
		return 0;
	}

	vector<vector<bool>> visit(row, vector<bool>(col));

	int dr[] = { 0,1,0,-1 };
	int dc[] = { 1,0,-1,0 };

	while (!bfs.empty()) {
		Tomato temp = bfs.front();
		bfs.pop();

		if (farm[temp.row][temp.col] != 1 || visit[temp.row][temp.col])
			continue;

		if (count < temp.count)
			count = temp.count;

		visit[temp.row][temp.col] = true;

		for (int i = 0; i < 4; i++) {
			int newRow = temp.row + dr[i];
			int newCol = temp.col + dc[i];

			if (newRow < 0 || newCol < 0 || newRow >= row || newCol >= col)
				continue;

			if (farm[newRow][newCol] != 0 || visit[newRow][newCol])
				continue;

			farm[newRow][newCol] = 1;
			bfs.push(Tomato(newRow, newCol, temp.count + 1));
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (!farm[i][j]) {
				cout << -1 << "";
				return 0;
			}
		}
	}

	cout << count << "\n";


	return 0;
}

int Solution::solution_251111_01()
{
	bool coloredPaper[101][101] = { false, };
	int N = 0;
	cin >> N;

	int answer = 0;

	for (int t = 0; t < N; t++) {
		int col, row = 0;
		cin >> col >> row;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (coloredPaper[row + i][col + j])
					continue;
				coloredPaper[row + i][col + j] = true;
				answer++;
			}
		}
	}

	cout << answer << endl;

	return 0;
}

int Solution::solution_251112_01()
{
	bool parentheses = false;
	string input;
	getline(cin, input);

	vector<char> sentences;

	for (int i = 0; i < input.length(); i++) {
		if (parentheses) {
			if (input.at(i) == '>')
				parentheses = false;
			cout << input.at(i);
		} else if (input.at(i) == '<' || input.at(i) == ' ') {
			parentheses = input.at(i) == '<';
			while (!sentences.empty()) {
				cout << sentences.back();
				sentences.pop_back();
			}
			cout << input.at(i);
		} else
			sentences.push_back(input.at(i));
	}

	while (!sentences.empty()) {
		cout << sentences.back();
		sentences.pop_back();
	}


	return 0;
}

int Solution::solution_251113_01()
{
	int N = 0;
	cin >> N;

	int answer = 0;
	int origin[91] = { 0, };

	if (N == 0) {
		cout << 0 << endl;
		return 0;
	}

	string input;
	cin >> input;
	for (int i = 0; i < input.length(); i++) {
		origin[(int)input.at(i)]++;
	}

	for (int i = 0; i < N - 1; i++) {
		string word;
		cin >> word;
		int sample[91] = { 0, };
		for (int j = 0; j < word.length(); j++) {
			sample[(int)word.at(j)]++;
		}

		int isDiff = 0;
		bool more = false;
		bool less = false;
		for (int j = 65; j < 91; j++) {
			int count = origin[j] - sample[j];
			if (count < -1 || count > 1) {
				isDiff = 2;
				break;
			}
			else if (count == 1) {
				if (more) {
					isDiff = 2;
					break;
				}
				else
					more = true;
			}
			else if (count == -1) {
				if (less) {
					isDiff = 2;
					break;
				}
				else
					less = true;
			}
		}

		if (isDiff < 2)
			answer++;
	}

	cout << answer << endl;

	return 0;
}

int Solution::solution_251114_01()
{
	int N, K = 0;
	cin >> N >> K;

	vector<int> coins;
	vector<long> dp(K + 1);

	for (int i = 0; i < N; i++) {
		int coin = 0;
		cin >> coin;
		coins.push_back(coin);
	}

	dp[0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = coins[i]; j <= K; j++) {
			dp[j] += dp[j - coins[i]];
		}
	}

	cout << dp[K] << endl;

	return 0;
}

void NandM_05(int index, vector<int>& stack, vector<bool>& visit, vector<int>& nums) {
	if (index >= stack.size()) {
		for (int idx : stack) {
			cout << nums[idx] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 0; i < nums.size(); i++) {
		if (!visit[i]) {
			visit[i] = true;
			stack[index] = i;
			NandM_05(index + 1, stack, visit, nums);
			visit[i] = false;
		}
	}
}

int Solution::solution_251115_01()
{
	int N, M = 0;
	cin >> N >> M;

	vector<bool> visit(N);
	vector<int> stack(M);
	vector<int> nums(N);

	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());
	NandM_05(0, stack, visit, nums);

	return 0;
}
