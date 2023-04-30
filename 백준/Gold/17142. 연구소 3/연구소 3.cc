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

int N, M, emp;
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
			else if (MAP[i][j] == 0)
				emp++;
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

void bfs() {
	queue<Node> q;
	memset(visited, -1, sizeof(visited));

	for (int i = 0; i < M; i++) {
		Node now = seln[i];
		q.push(now);
		visited[now.y][now.x] = 0;
	}
	int time = 0, area = 0;
	while (!q.empty())
	{
		
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx] != -1)
				continue;
			if (MAP[ny][nx] == 1)
				continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			if (MAP[ny][nx] == 0) {
				area++;
				time = visited[ny][nx];
			}
			q.push({ ny, nx });
		}
	}
	if(area == emp && ans > time)
		ans = time;
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
		dfs(i + 1, cnt + 1);
		seln.pop_back();
		used[i] = 0;
	}
}

void solve() {
	if (emp == 0) {
		printf("0\n");
		return;
	}
	dfs(0, 0);
	if (ans == 21e8) ans = -1;
	else ans = ans;
	printf("%d\n", ans);
}

int main() {
	input();
	solve();
	return 0;
}