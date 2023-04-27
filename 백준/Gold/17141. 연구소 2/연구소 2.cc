#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
	int y, x;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M;
int MAP[51][51];

int visited[51][51];

vector<Node> v;
int ans = 21e8;

int used[11];
vector<Node> seln;

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &MAP[i][j]);
			if (MAP[i][j] == 2)
				v.push_back({ i, j });
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

bool check() {
	int mx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int tmp = visited[i][j];
			if (MAP[i][j] == 1) continue;
			if (!tmp) return 0;
			if (mx < tmp) mx = tmp;	
		}
	}

	if (mx < ans) ans = mx;
	return 1;
}

void bfs() {
	queue<Node> q;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < M; i++) {
		Node now = seln[i];
		q.push(now);
		visited[now.y][now.x] = 1;
	}

	while (!q.empty())
	{
		int cursize = q.size();
		for (int c = 0; c < cursize; c++) {
			Node now = q.front();
			q.pop();
			if (visited[now.y][now.x] >= ans)
				return;
			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (outRange(ny, nx))
					continue;
				if (visited[ny][nx])
					continue;
				if (MAP[ny][nx] == 1)
					continue;
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny, nx });
			}
		}
	}
	check();
}

void dfs(int now, int cnt) {
	// 기저조건 -> M개를 고르면 종료
	if (cnt == M) {
		bfs();
		return;
	}
	// 재귀 구성
	for (int i = now; i < v.size(); i++) {
		if (used[i])
			continue;
		used[i] = 1;
		Node tmp = v[i];
		seln.push_back(tmp);
		dfs(i, cnt + 1);
		seln.pop_back();
		used[i] = 0;
	}
}

void solve() {
	dfs(0, 0);
	if (ans == 21e8) ans = -1;
	else ans -= 1;
	printf("%d\n", ans);
}

int main() {
	input();
	solve();
	return 0;
}