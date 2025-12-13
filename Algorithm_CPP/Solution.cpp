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

	sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
		return a + b > b + a;
		});

	if (!strs.empty() && strs[0] == "0") {
		return "0";
	}

	for (string& s : strs) {
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

void dfs_250530_01(int& node, vector<vector<int>>& computers, vector<bool>& visit) {
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

void normalize(Shape& shape) {
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

Shape extractShape(int sr, int sc, vector<vector<int>>& board, int target) {
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

Shape rotate90(const Shape& shape) {
	Shape rotated;
	for (int i = 0; i < shape.size(); i++) {
		int r = shape[i].first;
		int c = shape[i].second;
		rotated.push_back({ c, -r });
	}
	normalize(rotated);
	return rotated;
}

bool isMatch(const Shape& hole, Shape block) {
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

void dfs_250613(int index, int& count, vector<bool>& visit, vector<vector<int>>& vecNodes) {
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

bool friendship(int node, int index, vector<bool>& visit, vector<vector<int>>& friends) {
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

	Node() {};

	Node(int next, int distance) {
		this->next = next;
		this->distance = distance;
	}
};

void bfs_250608(int& index, int& max, vector<vector<Node>>& tree) {
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
		}
		else if (input.at(i) == '<' || input.at(i) == ' ') {
			parentheses = input.at(i) == '<';
			while (!sentences.empty()) {
				cout << sentences.back();
				sentences.pop_back();
			}
			cout << input.at(i);
		}
		else
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

void missSsafy(int index, int N) {
	string prefix = "";
	for (int i = 0; i < index; i++) {
		prefix += "____";
	}

	if (index >= N) {
		cout << prefix + "\"재귀함수가 뭔가요?\"\n"
			<< prefix + "\"재귀함수는 자기 자신을 호출하는 함수라네\"\n"
			<< prefix + "라고 답변하였지.\n";
		return;
	}


	cout << prefix + "\"재귀함수가 뭔가요?\"\n"
		<< prefix + "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n"
		<< prefix + "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n"
		<< prefix + "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n";
	missSsafy(index + 1, N);
	cout << prefix + "라고 답변하였지.\n";
}

int Solution::solution_251116_01() {
	int N = 0;
	cin >> N;

	cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n";

	missSsafy(0, N);

	return 0;
}

bool akaraka(string& input) {
	if (input.length() <= 1)
		return true;

	int left = 0;
	int right = input.length() - 1;
	while (left < right) {
		if (input.at(left) != input.at(right))
			return false;

		left++;
		right--;
	}

	string leftHalf = input.substr(0, input.length() / 2);
	string rightHalf = input.substr(input.length() / 2 + input.length() % 2, input.length());

	return akaraka(leftHalf) && akaraka(rightHalf);
}

int Solution::solution_251117_01()
{
	string input = "";
	cin >> input;

	if (input.length() == 1) {
		cout << "AKARAKA\n";
		return 0;
	}

	bool isAkaraka = true;
	isAkaraka = akaraka(input);

	if (isAkaraka)	cout << "AKARAKA\n";
	else			cout << "IPSELENTI\n";

	return 0;
}

class tomato_251118 {
public:
	tomato_251118(int z, int row, int col, int count) {
		this->z = z;
		this->row = row;
		this->col = col;
		this->count = count;
	}

	int row;
	int col;
	int z;
	int count;
};

int Solution::solution_251118_01()
{
	int M = 0, N = 0, H = 0;
	cin >> M >> N >> H;

	int result = 0;

	vector<vector<vector<bool>>> visit(H, vector<vector<bool>>(N, vector<bool>(M, false)));;
	vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M, 0)));

	queue<tomato_251118> queue;

	int dr[] = { 0,0,1,-1,0,0 };
	int dc[] = { 1,-1,0,0,0,0 };
	int du[] = { 0,0,0,0,1,-1 };

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> box[i][j][k];
				if (box[i][j][k] == 1)
					queue.push(tomato_251118(i, j, k, 0));
			}
		}
	}

	while (!queue.empty()) {
		tomato_251118 temp = queue.front();
		queue.pop();

		if (result < temp.count)
			result = temp.count;

		for (int i = 0; i < 6; i++) {
			int newZ = temp.z + du[i];
			int newRow = temp.row + dr[i];
			int newCol = temp.col + dc[i];

			if (newZ < 0 || newRow < 0 || newCol < 0 || newZ >= H || newRow >= N || newCol >= M)
				continue;

			if (box[newZ][newRow][newCol] != 0)
				continue;

			box[newZ][newRow][newCol] = 1;
			queue.push(tomato_251118(newZ, newRow, newCol, temp.count + 1));
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (box[i][j][k] == 0) {
					result = -1;
					break;
				}
			}
		}
	}

	cout << result << "\n";

	return 0;
}

int Solution::solution_251119_01()
{
	string input;
	string bomb;

	vector<char> word;
	vector<char> stack;

	cin >> input >> bomb;

	for (int i = 0; i < input.length(); i++)
		word.push_back(input.at(i));

	while (!word.empty()) {
		int index = word.size() - bomb.length();
		if (index < 0)
			break;

		bool isBomb = true;
		int bombIndex = 0;
		for (int i = 0; i < bomb.length(); i++) {
			if (word[index + i] != bomb[i]) {
				isBomb = false;
				break;
			}
		}

		if (isBomb) {
			for (int i = 0; i < bomb.length(); i++)
				word.pop_back();

			int size = bomb.length();
			while (!stack.empty() && size > 1) {
				word.push_back(stack.back());
				stack.pop_back();
				size--;
			}
		} else {
			stack.push_back(word.back());
			word.pop_back();
		}
	}

	while (!word.empty()) {
		stack.push_back(word.back());
		word.pop_back();
	}

	if (stack.empty())
		cout << "FRULA\n";
	else {
		for (int i = stack.size() - 1; i >= 0; i--)
			cout << stack[i];
	}

	return 0;
}

int Solution::solution_251120_01()
{
	int N, K;
	cin >> N >> K;

	vector<pair<int, int>> values(N);
	for (int i = 0; i < N; i++)
		cin >> values[i].first >> values[i].second;

	vector<int> dp(K + 1, 0);

	for (int i = 0; i < N; i++) {
		int w_i = values[i].first;
		int v_i = values[i].second;

		for (int w = K; w >= w_i; --w) {
			dp[w] = max(dp[w], dp[w - w_i] + v_i);
		}
	}

	cout << dp[K];

	return 0;
}

class Happy_251121 {
public:
	int index;
	int x;
	int y;
	int beer;
	Happy_251121(int index, int x, int y, int beer) {
		this->index = index;
		this->x = x;
		this->y = y;
		this->beer = beer;
	}
};

bool compareStore_251121(pair<int, int> a, pair<int, int> b) {

	if (a.first != b.first)
		return a.first < b.first;
	else
		return a.second < b.second;

}

int Solution::solution_251121_01()
{
	int T = 0, N = 0;
	int minCoordinate = -32768;
	int maxCoordinate = 32767;

	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N;
		pair<int, int> home;
		pair<int, int> festival;

		vector<pair<int, int>> store(N);
		vector<bool> visitStore(N);

		cin >> home.first >> home.second;
		for (int i = 0; i < N; i++)
			cin >> store[i].first >> store[i].second;

		sort(store.begin(), store.end(), compareStore_251121);

		cin >> festival.first >> festival.second;

		queue<Happy_251121> queue;
		queue.push(Happy_251121(0, home.first, home.second, 20));

		string result = "sad";
		while (!queue.empty()) {
			Happy_251121 temp = queue.front();
			queue.pop();

			int diffXToFestival = abs(festival.first - temp.x);
			int diffYToFestival = abs(festival.second - temp.y);

			int maxDistance = temp.beer * 50;
			if (diffXToFestival + diffYToFestival <= maxDistance) {
				result = "happy";
				break;
			}

			for (int i = 0; i < store.size(); i++) {
				int diffXToStore = abs(store[i].first - temp.x);
				int diffYToStore = abs(store[i].second - temp.y);

				int maxDistance = temp.beer * 50;
				if (diffXToStore + diffYToStore <= maxDistance && !visitStore[i]) {
					visitStore[i] = true;
					queue.push(Happy_251121(i, store[i].first, store[i].second, 20));
				}
			}

		}
		cout << result << "\n";
	}
	return 0;
}

int Solution::solution_251122_01() {

	bool nums[10000] = { false, };
	for (int i = 1; i < 10000; i++) {
		int nTemp = i;
		int nSum = i;
		while (nTemp > 0) {
			nSum += nTemp % 10;
			nTemp /= 10;
		}
		if (nSum < 10000)
			nums[nSum] = true;
	}

	for (int i = 1; i < 10000; i++) {
		if (!nums[i])
			cout << i << "\n";
	}

	return 0;
}

int Solution::solution_251123_01() {

	int R = 0, C = 0, N = 0;
	cin >> R >> C >> N;

	vector<vector<int>> map(R, vector<int>(C));
	for (int i = 0; i < R; i++) {
		string line = "";
		cin >> line;
		for (int j = 0; j < C; j++) {
			if (line.at(j) == 'O')
				map[i][j] = 2;
		}
	}

	int dr[] = { 0,0,1,-1 };
	int dc[] = { 1,-1,0,0 };
	for (int n = 0; n < N - 1; n++) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (map[i][j] > 0) {
					map[i][j]--;;
				} else
					map[i][j] = 3;

			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (!map[i][j]) {
					for (int d = 0; d < 4; d++) {
						int newRow = dr[d] + i;
						int newCol = dc[d] + j;
						if (newRow < 0 || newCol < 0 || newRow >= R || newCol >= C)
							continue;
						if (map[newRow][newCol] > 1)
							map[newRow][newCol] = -1;
					}
				}
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] > 0)
				cout << "O";
			else
				cout << ".";
		}
		cout << "\n";
	}

	return 0;
}

bool compare_251124(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)
		return a.first < b.first;

	return a.second < b.second;
}

int Solution::solution_251124_01()
{
	int M = 0, N = 0;

	cin >> M >> N;
	vector<vector<pair<int, int>>> multiverse(M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			pair<int, int> temp;
			cin >> temp.first;
			temp.second = j;
			multiverse[i].push_back(temp);
		}
	}

	for (int i = 0; i < M; i++)
		std::sort(multiverse[i].begin(), multiverse[i].end(), compare_251124);

	vector<vector<pair<int, int>>> ranks(M);
	for (int i = 0; i < M; i++) {
		int rank = 0;
		for (int j = 0; j < N - 1; j++) {
			pair<int, int> temp;
			temp.first = multiverse[i][j].second;
			temp.second = rank;
			ranks[i].push_back(temp);
			if (multiverse[i][j].first != multiverse[i][j + 1].first)
				rank++;
		}
		pair<int, int> temp;
		temp.first = multiverse[i][N - 1].second;
		temp.second = rank;
		ranks[i].push_back(temp);
	}

	int result = 0;
	for (int i = 0; i < M - 1; i++) {
		for (int j = i + 1; j < M; j++) {
			bool isMultiverse = true;
			for (int k = 0; k < N; k++) {
				if (ranks[i][k].first != ranks[j][k].first
					|| ranks[i][k].second != ranks[j][k].second) {
					isMultiverse = false;
					break;
				}
			}
			if (isMultiverse)
				result++;
		}
	}

	cout << result;
	return 0;
}

int Solution::solution_251125_01()
{
	int N = 0, K = 0;
	cin >> N >> K;

	vector<int> sensors(N);
	for (int i = 0; i < N; i++) {
		cin >> sensors[i];
	}

	if (K == N) {
		cout << '0';
		return 0;
	}

	sort(sensors.begin(), sensors.end());
	vector<int> distances;
	for (int i = 0; i < N - 1; i++)
		distances.push_back(sensors[i + 1] - sensors[i]);

	sort(distances.begin(), distances.end());

	for (int i = 0; i < K - 1; i++) {
		if (distances.empty())
			break;

		distances.pop_back();
	}

	int sum = 0;
	for (int d : distances)
		sum += d;

	cout << sum;

	return 0;
}

struct Node_251126 {
    char value;
    bool isEnd;
    unordered_map<char, Node_251126*> children;

	Node_251126(char ch) : value(ch), isEnd(false) {}

    ~Node_251126() {
        for (auto kv : children) {
            delete kv.second;
        }
    }
};

int Solution::solution_251126_01()
{
	int T = 0;
	cin >> T;

	for (int t = 0; t < T; t++) {
		int N = 0;
		cin >> N;

		vector<string> numbers(N);
		for (int i = 0; i < N; i++)
			cin >> numbers[i];


		Node_251126* head = new Node_251126('h');
		bool isSingle = true;

		for (string s : numbers) {
			Node_251126* node = head;

			for (int i = 0; i < s.length(); i++) {
				auto it = node->children.find(s[i]);

				if (it == node->children.end()) {
					Node_251126* child = new Node_251126(s[i]);
					node->children[s[i]] = child;
					node = child;
				}
				else {
					node = it->second;
				}

				if (node->isEnd && i != s.length() - 1) {
					isSingle = false;
					break;
				}
			}

			if (!isSingle) break;

			if (!node->children.empty()) {
				isSingle = false;
				break;
			}

			node->isEnd = true;
		}

		if (isSingle)
			cout << "YES\n";
		else
			cout << "NO\n";

		delete head;
	}
	return 0;
}

int Solution::solution_251127_01() {

	int N = 0, Q = 0;

	cin >> N >> Q;
	vector<vector<pair<int, int>>> mootube(N + 1);

	for (int i = 0; i < N - 1; i++) {
		int first = 0, second = 0, usado = 0;
		cin >> first >> second >> usado;
		pair<int, int> temp;
		temp.first = second;
		temp.second = usado;
		mootube[first].push_back(temp);
		temp.first = first;
		mootube[second].push_back(temp);
	}

	for (int i = 0; i < Q; i++) {
		int k = 0, v = 0, count = 0;
		cin >> k >> v;
		queue<int> moo;
		moo.push(v);
		vector<bool> visit(N + 1, false);

		while (!moo.empty()) {
			int temp = moo.front();
			moo.pop();
			if (visit[temp])
				continue;

			visit[temp] = true;
			for (int m = 0; m < mootube[temp].size(); m++) {
				int next = mootube[temp][m].first;
				int usado = mootube[temp][m].second;

				if (!visit[next] && k <= usado) {
					moo.push(next);
					count++;
				}
			}
		}
		cout << count << '\n';
	}


	return 0;
}

int Solution::solution_251128_01()
{
	int N = 0, M = 0;
	cin >> N >> M;

	vector<vector<int>> vecCity(N + 1);

	for (int i = 0; i < N; i++) {
		vector<int> temp;
		for (int j = 0; j < N; j++) {
			int city = 0;
			cin >> city;
			if (city) {
				temp.push_back(j + 1);
			}
		}
		if (!temp.empty())
			vecCity[i + 1] = temp;
	}

	vector<int> plan(M);
	for (int i = 0; i < M; i++)
		cin >> plan[i];

	vector<vector<bool>> ablePlan(N + 1, vector<bool>(N + 1, false));
	for (int i = 0; i < M - 1; i++) {
		bool bAble = false;
		int start = plan[i];
		int end = plan[i + 1];

		if (ablePlan[start][end] || ablePlan[end][start])
			continue;

		queue<int> bfs;
		bfs.push(start);
		vector<bool> visit(N + 1, false);
		while (!bfs.empty()) {
			int temp = bfs.front();
			bfs.pop();
			if (temp == end) {
				bAble = true;
				ablePlan[start][end] = true;
				ablePlan[end][start] = true;
				break;
			}

			if (visit[temp])
				continue;
			visit[temp] = true;

			for (int j = 0; j < vecCity[temp].size(); j++) {
				int next = vecCity[temp][j];
				if (!visit[next]) {
					bfs.push(next);
				}
			}
		}

		if (!bAble) {
			cout << "NO\n";
			return 0;
		}
	}

	cout << "YES\n";
	return 0;
}

int Solution::solution_251129_01() {

	int N = 0;
	cin >> N;
	vector<vector<int>> hall(N, vector<int>(N, 0));
	queue<pair<int, int>> teacher;

	for (int i = 0; i < N; i++) {
		vector<int> temp(N);
		for (int j = 0; j < N; j++) {
			char s = 'X';
			cin >> s;
			if (s == 'S')
				temp[j] = 1;
			if (s == 'T') {
				temp[j] = 2;
				pair<int, int> loc;
				loc.first = i;
				loc.second = j;
				teacher.push(loc);
			}
		}
		hall[i] = temp;
	}

	int count = 3;
	int dr[] = { 0,0,1,-1 };
	int dc[] = { 1,-1,0,0 };
	while (!teacher.empty()) {
		pair<int, int> temp = teacher.front();
		teacher.pop();

		for (int i = 0; i < 4; i++) {
			int newRow = temp.first + dr[i];
			int newCol = temp.second + dc[i];

			while (newCol >= 0 && newRow >= 0 && newCol < N && newRow < N) {
				if (hall[newRow][newCol] == 1) {
					int preRow = newRow - dr[i];
					int preCol = newCol - dc[i];
					if (preRow >= 0 && preCol >= 0 && preRow < N && preCol < N) {
						if (!hall[preRow][preCol]) {
							count--;
							if (count < 0) {
								cout << "NO";
								return 0;
							}
							hall[preRow][preCol] = 3;
							break;
						} else if (hall[preRow][preCol] == 2) {
							cout << "NO";
							return 0;
						}
					}
				} else if (hall[newRow][newCol] > 1)
					break;

				newRow += dr[i];
				newCol += dc[i];
			}
		}
	}

	return 0;
}

int Solution::solution_251201_01()
{
	int N = 0;
	cin >> N;
	vector<long> vecX;
	vector<long> vecY;
	for (int i = 0; i < N; i++) {
		long x = 0, y = 0;
		cin >> x >> y;
		vecX.push_back(x);
		vecY.push_back(y);
	}

	long sum = 0;
	for (int i = 0; i < N - 1; i++) {
		sum += vecX[i] * vecY[i + 1] - vecX[i + 1] * vecY[i];
	}
	sum += vecX[N - 1] * vecY[0] - vecX[0] * vecY[N - 1];
	double answer = (double)llabs(sum) / 2.0;

	cout << fixed;
	cout.precision(1);
	cout << answer;
	return 0;
}

int Solution::solution_251202_01()
{
	string S, T;
	cin >> S >> T;

	queue<string> search;
	search.push(T);

	while (!search.empty()) {
		string temp = search.front();
		search.pop();

		if (temp == S) {
			cout << 1;
			return 0;
		}

		if (temp.empty() || temp.length() < S.length() || temp.length() == 1)
			continue;

		if (temp.at(0) == 'B') {
			string next;
			for (int i = 1; i < temp.length(); i++) {
				next.push_back(temp.at(temp.length() - i));
			}
			search.push(next);
		}

		if (temp.length() == 1 && temp == "A")
			search.push("A");

		if (temp.at(temp.length() - 1) == 'A') {
			search.push(temp.substr(0, temp.length() - 1));
		}
	}

	cout << 0;

	return 0;
}

int Solution::solution_251203_01()
{
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int N = 0;
		cin >> N;
		vector<vector<int>> stickers(2, vector<int>(N + 1, 0));
		vector<vector<int>> dp(2, vector<int>(N + 1, 0));

		for (int i = 0; i < 2; i++) {
			vector<int> temp(N + 1);
			for (int j = 1; j <= N; j++)
				cin >> temp[j];
			stickers[i] = temp;
		}
		dp[0][1] = stickers[0][1];
		dp[1][1] = stickers[1][1];

		for (int i = 2; i <= N; i++) {
			dp[0][i] = max(dp[1][i - 1], dp[1][i - 2]) + stickers[0][i];
			dp[1][i] = max(dp[0][i - 1], dp[0][i - 2]) + stickers[1][i];
		}

		cout << max(dp[0][N], dp[1][N]) << "\n";
	}

	return 0;
}

class Robot_251204 {
public:
	int row;
	int col;
	int direction;
	Robot_251204(int r, int c, int d) {
		row = r;
		col = c;
		direction = d;
	}
};


int Solution::solution_251204_01()
{
	int N = 0, M = 0, startRow, startCol, startDirection = 0;
	cin >> N >> M >> startRow >> startCol >> startDirection;

	vector<vector<int>> room;

	for (int i = 0; i < N; i++) {
		vector<int> temp(M);
		for (int j = 0; j < M; j++) {
			cin >> temp[j];
		}
		room.push_back(temp);
	}

	int dr[] = { -1,0,1,0 };
	int dc[] = { 0,1,0,-1 };

	queue<Robot_251204> search;
	search.push(Robot_251204(startRow, startCol, startDirection));
	while (!search.empty()) {
		Robot_251204 temp = search.front();
		search.pop();

		if (!room[temp.row][temp.col])
			room[temp.row][temp.col] = 2;

		bool isClean = true;
		for (int i = 0; i < 4; i++) {
			int newRow = dr[i] + temp.row;
			int newCol = dc[i] + temp.col;

			if (newRow < 0 || newCol < 0 || newRow >= N || newCol >= M)
				continue;

			if (!room[newRow][newCol]) {
				isClean = false;
				break;
			}
		}

		if (isClean) {
			int backDirection = (temp.direction + 2) % 4;
			int backRow = dr[backDirection] + temp.row;
			int backCol = dc[backDirection] + temp.col;

			if (backRow < 0 || backCol < 0 || backRow >= N || backCol >= M || room[backRow][backCol] == 1)
				break;

			search.push(Robot_251204(backRow, backCol, temp.direction));
		}
		else {
			for (int i = 1; i <= 4; i++) {
				int rotateDirection = temp.direction - i;
				if (rotateDirection < 0)
					rotateDirection += 4;

				int nextRow = dr[rotateDirection] + temp.row;
				int nextCol = dc[rotateDirection] + temp.col;

				if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M || room[nextRow][nextCol])
					continue;

				search.push(Robot_251204(nextRow, nextCol, rotateDirection));
				break;
			}

		}
	}

	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (room[i][j] == 2)
				count++;
		}
	}

	cout << count;

	return 0;
}

int Solution::solution_251205_01()
{
	int T = 0;
	cin >> T;

	for (int t = 0; t < T; t++) {
		string W;
		int K = 0;
		cin >> W >> K;

		vector<vector<int>> vecIndex(150);
		int chCounts[150] = { 0, };
		for (int i = 0; i < W.length(); i++) {
			chCounts[W.at(i)]++;
			vecIndex[W.at(i)].push_back(i);
		}

		vector<int> gameCh;
		for (int i = 97; i <= 122; i++) {
			if (chCounts[i] >= K)
				gameCh.push_back(i);
		}

		if (gameCh.empty()) {
			cout << -1 << "\n";
			continue;
		}

		if (K == 1) {
			cout << 1 << " " << 1 << "\n";
			continue;
		}

		int maxD = 0;
		int minD = 10000;
		for (int i = 0; i < gameCh.size(); i++) {
			int idx = gameCh[i];
			int left = 0;
			int right = 1;
			while (right < vecIndex[idx].size()) {
				if (right - left + 1 < K)
					right++;
				else if (right - left + 1 == K) {
					int distance = vecIndex[idx][right] - vecIndex[idx][left] + 1;
					maxD = max(maxD, distance);
					minD = min(minD, distance);
					left++;
				}
			}
		}

		cout << minD << " " << maxD << "\n";
	}

	return 0;
}

int result_251208;
int N_251208;
vector<int> numbers_251208;
vector<int> space_251208;
vector<bool> visit_251208;
set<int> resultSet_251208;

void pickNumbers(int index) {
	if (index > N_251208)
		return;

	if (visit_251208[index])
		return;

	visit_251208[index] = true;
	space_251208.push_back(index);

	int next = numbers_251208[index];

	if (!visit_251208[next]) {
		pickNumbers(next);
	} else {
		auto it = find(space_251208.begin(), space_251208.end(), next);
		if (it != space_251208.end()) {
			for (; it != space_251208.end(); it++)
				resultSet_251208.insert(*it);
		}
	}
}

int Solution::solution_251208_01()
{
	N_251208 = 0;
	result_251208 = 0;
	cin >> N_251208;
	numbers_251208.resize(N_251208 + 1, 0);
	for (int i = 1; i <= N_251208; i++)
		cin >> numbers_251208[i];

	for (int i = 1; i <= N_251208; i++) {
		visit_251208.resize(N_251208 + 1, false);
		space_251208.clear();
		pickNumbers(i);
	}

	cout << resultSet_251208.size() << "\n";
	for (int num : resultSet_251208)
		cout << num << "\n";


	return 0;
}

int Solution::solution_251209_01()
{
	int H = 0, W = 0, result = 0;
	cin >> H >> W;

	vector<int> blocks(W);
	for (int i = 0; i < W; i++)
		cin >> blocks[i];

	int left = 0;
	while (left < W && blocks[left] == 0)
		left++;

	if (left >= W) {
		cout << 0;
		return 0;
	}

	int right = W - 1;
	int leftMax = blocks[left];
	int rightMax = blocks[right];

	while (left < right) {
		if (blocks[left] <= blocks[right]) {
			left++;
			leftMax = max(leftMax, blocks[left]);
			result += leftMax - blocks[left];
		} else {
			right--;
			rightMax = max(rightMax, blocks[right]);
			result += rightMax - blocks[right];
		}
	}

	cout << result;

	return 0;
}

class Way {
public:
	int next;
	int cow;
	Way() { next = 0; cow = 0; };
	Way(int n, int c) {
		next = n;
		cow = c;
	}

	bool operator>(const Way& other) const {
		return cow > other.cow;
	}
};

int Solution::solution_251210_01()
{
	int N = 0, M = 0;
	cin >> N >> M;
	vector<vector<Way>> ways(N + 1);
	for (int i = 0; i < M; i++) {
		int A = 0, B = 0, C = 0;
		cin >> A >> B >> C;
		ways[A].push_back(Way(B, C));
		ways[B].push_back(Way(A, C));
	}

	vector<int> dijkstra(N + 1, INT32_MAX);
	vector<bool> visit(N + 1, false);

	priority_queue<Way, vector<Way>, greater<Way>> pq;

	dijkstra[1] = 0;
	pq.push(Way(1, 0));
	while (!pq.empty()) {
		int index = pq.top().next;
		int cost = pq.top().cow;
		pq.pop();

		if (visit[index])
			continue;
		visit[index] = true;

		if (index == N)
			break;

		for (int j = 0; j < (int)ways[index].size(); j++) {
			int next = ways[index][j].next;
			if (visit[next])
				continue;

			int cow = ways[index][j].cow;
			if (dijkstra[next] > cost + cow) {
				dijkstra[next] = cost + cow;
				pq.push(Way(next, dijkstra[next]));
			}
		}
	}

	cout << dijkstra[N];

	return 0;
}

int getDiff_251211(int x, int y, const vector<vector<bool>>& digit, int K)
{
	int diff = 0;

	for (int pos = 0; pos < K; ++pos) {
		int dx = x % 10;
		int dy = y % 10;
		x /= 10;
		y /= 10;

		for (int s = 0; s < 7; ++s) {
			if (digit[dx][s] != digit[dy][s]) {
				diff++;
			}
		}
	}

	return diff;
}

int Solution::solution_251211_01()
{
	int N = 0, K = 0, P = 0, X = 0;

	cin >> N >> K >> P >> X;

	vector<vector<bool>> digit(10, vector<bool>(7, true));

	//  
	//0 1 2
	//  3
	//4 5 6
	// 
	digit[0][3] = false;

	digit[1][0] = false;
	digit[1][1] = false;
	digit[1][3] = false;
	digit[1][4] = false;
	digit[1][5] = false;

	digit[2][0] = false;
	digit[2][6] = false;

	digit[3][0] = false;
	digit[3][4] = false;

	digit[4][1] = false;
	digit[4][4] = false;
	digit[4][5] = false;

	digit[5][2] = false;
	digit[5][4] = false;

	digit[6][2] = false;

	digit[7][0] = false;
	digit[7][3] = false;
	digit[7][4] = false;
	digit[7][5] = false;

	digit[9][4] = false;

	int result = 0;

	for (int floor = 1; floor <= N; ++floor) {
		if (floor == X)
			continue;

		int diff = getDiff_251211(X, floor, digit, K);

		if (diff >= 1 && diff <= P) {
			result++;
		}
	}
	cout << result;

	return 0;
}

void makeZero(int index, int before, int next, string result, vector<string>& zeros, int N) {
	if (index > N) {
		string line = result;
		line.erase(remove(line.begin(), line.end(), ' '), line.end());

		vector<char> oper;
		vector<int> nums;

		string numStr;
		for (int i = 0; i < line.length(); i++) {
			if (line.at(i) == '+' || line.at(i) == '-') {
				nums.push_back(stoi(numStr));
				numStr.clear();
				oper.push_back(line.at(i));
			} else {
				numStr.push_back(line.at(i));
			}
		}

		if (oper.empty())
			return;

		if (!numStr.empty())
			nums.push_back(stoi(numStr));

		int sum = nums.at(0);
		for (int i = 0; i < oper.size(); i++) {
			if (oper[i] == '+')
				sum += nums.at(i + 1);
			else
				sum -= nums.at(i + 1);
		}

		if (sum == 0)
			zeros.push_back(result);

		return;
	}

	int nextIndex = index + 1;
	char indexCh = index + '0';

	makeZero(nextIndex, index, nextIndex, result + '+' + indexCh, zeros, N);
	makeZero(nextIndex, index, nextIndex, result + '-' + indexCh, zeros, N);
	makeZero(nextIndex, next, before * 10 + index, result + ' ' + indexCh, zeros, N);
}

int Solution::solution_251212_01()
{
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int N = 0;
		cin >> N;

		vector<string> zeros;
		string result;
		result.push_back('0' + 1);

		makeZero(2, 1, 2, result, zeros, N);
		sort(zeros.begin(), zeros.end());

		for (string str : zeros) {
			cout << str << "\n";
		}
		cout << "\n";
	}

	return 0;
}

class Zelda {
public:
	int next;
	int luffy;
	Zelda() {}
	Zelda(int n, int l) {
		next = n;
		luffy = l;
	}

	bool operator> (const Zelda& other) const {
		return luffy > other.luffy;
	}
};

int Solution::solution_251213_01() {
	int N = 0;
	int testIndex = 1;

	int dr[] = { 0,0,1,-1 };
	int dc[] = { 1,-1,0,0 };

	while (N >= 0) {
		cin >> N;
		if (N == 0)
			return 0;

		vector<int> luffy(N * N);
		for (int i = 0; i < N * N; i++) {
			cin >> luffy[i];
		}

		vector<vector<Zelda>> cave(N * N);

		int caveIndex = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int d = 0; d < 4; d++) {
					int nextRow = dr[d] + i;
					int nextCol = dc[d] + j;

					if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N)
						continue;

					if (d == 0)   cave[caveIndex].push_back(Zelda(caveIndex + 1, luffy[caveIndex + 1]));
					if (d == 1)   cave[caveIndex].push_back(Zelda(caveIndex - 1, luffy[caveIndex - 1]));
					if (d == 2)   cave[caveIndex].push_back(Zelda(caveIndex + N, luffy[caveIndex + N]));
					if (d == 3)   cave[caveIndex].push_back(Zelda(caveIndex - N, luffy[caveIndex - N]));
				}
				caveIndex++;
			}
		}

		vector<int> daijk(N * N, INT32_MAX);
		vector<bool> visit(N * N, false);
		priority_queue<Zelda, vector<Zelda>, greater<Zelda>> pq;

		daijk[0] = luffy[0];
		pq.push(Zelda(0, luffy[0]));
		while (!pq.empty()) {
			Zelda temp = pq.top();
			pq.pop();

			int now = temp.next;
			int nowLuffy = temp.luffy;

			if (visit[now])
				continue;

			visit[now] = true;

			for (int i = 0; i < cave[now].size(); i++) {
				int nextNum = cave[now][i].next;
				int nextLuffy = cave[now][i].luffy;
				if (visit[nextNum])
					continue;

				if (daijk[nextNum] > daijk[now] + nextLuffy) {
					daijk[nextNum] = daijk[now] + nextLuffy;
					pq.push(Zelda(nextNum, daijk[nextNum]));
				}
			}

		}
		cout << "Problem " << testIndex++ << ": " << daijk[N * N - 1] << "\n";
	}

	return 0;
}
