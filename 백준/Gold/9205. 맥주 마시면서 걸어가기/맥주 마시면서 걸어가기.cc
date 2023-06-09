#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct Node {
	int y, x;
};

int N;
Node store[101];
int sy, sx, dy, dx;

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void init() {
	memset(store, 0, sizeof(store));
}

void input() {
	cin >> N;
	cin >> sy >> sx;
	for (int i = 0; i < N; i++) {
		int y, x;
		cin >> y >> x;
		Node now = { y, x };
		store[i] = now;
	}
	cin >> dy >> dx;
}

bool bfs() {
	queue<Node> q;
	q.push({ sy, sx });

	int visited[101] = { 0, };

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();
		int dist = getDist(dx, dy, now.x, now.y);
		if (dist <= 1000)
			return 1;
		for (int i = 0; i < N; i++) {
			if (visited[i]) continue;
			Node nx = store[i];

			dist = getDist(nx.x, nx.y, now.x, now.y);
			if (dist > 1000) continue;

			visited[i] = 1;
			q.push(nx);
		}
	}
	return 0;
}

int main() {
	fastIO;
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		init();
		string ans = "sad";
		// input
		input();
		// solve
		int flag = bfs();
		if (flag) ans = "happy";
		// output
		cout << ans << '\n';
	}
	return 0;
}