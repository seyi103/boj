#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;
#define MXN 1001

struct Node {
	int y, x, block;
};

int N, M;
int MAP[MXN][MXN];

int visited[MXN][MXN][2]; // 0: 벽을 부숨, 1: 안부숨
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

bool outRange(int y, int x) {
	return y < 0 || y >= N || x < 0 || x >= M;
}

void bfs(int y, int x) {
	queue<Node> q;
	q.push({ y, x, 1 });

	visited[y][x][1] = 1;

	while (!q.empty())
	{
		Node now = q.front(); q.pop();
		if (now.y == N - 1 && now.x == M - 1) {
			cout << visited[now.y][now.x][now.block];
			return;
		}
		for (int i = 0; i < 4; ++i) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx)) continue;
			// #1. 벽이고 뚫을 수 있음
			if (MAP[ny][nx] && now.block) {
				visited[ny][nx][now.block - 1] = visited[now.y][now.x][now.block] + 1;
				q.push({ ny, nx, 0 });
			}
			// #2. 빈칸이고 방문 x
			else if (!MAP[ny][nx] && !visited[ny][nx][now.block]) {
				visited[ny][nx][now.block] = visited[now.y][now.x][now.block] + 1;
				q.push({ ny, nx, now.block });
			}
		}
	}
	cout << "-1\n";
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			char tmp;
			cin >> tmp;
			MAP[i][j] = tmp - '0';
		}
	}

	bfs(0, 0);
}

int main() {
	fastIO;
	solve();
	return 0;
}