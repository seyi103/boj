#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
using pi = pair<int, int>;
#define MXN 100

int N;
int MAP[MXN][MXN];
int mx, mi, ans; // 높이 정보의 최대, 최소
int visited[MXN][MXN];

int ydir[] = { 0,0,-1,1 };
int xdir[] = { -1,1,0,0 };

/*
기본 설계
- 최저 높이 + 1 부터 최대 높이 -1 까지 모든 높이의 비를 내려본다
- 안전한 영역 확인
- 최대값 저장
*/

void input() {
	mx = -21e8;
	mi = 21e8;
	ans = 0;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> MAP[i][j];
			int num = MAP[i][j];
			if (num < mi) mi = num;
			if (num > mx) mx = num;
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || y >= N || x < 0 || x >= N;
}

void bfs(int y, int x, int lim) {
	queue<pi> q;
	q.push({ y, x });

	visited[y][x] = 1;
	
	while (!q.empty())
	{
		pi now = q.front(); q.pop();
		for (int i = 0; i < 4; ++i) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (outRange(ny, nx) || visited[ny][nx] || MAP[ny][nx] <= lim) continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
}

void solve() {
	for (int i = mi; i <= mx - 1; ++i) {
		int cnt = 0;
		memset(visited, 0, sizeof(visited));
		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < N; ++x) {
				if (MAP[y][x] > i && !visited[y][x]) {
					bfs(y, x, i);
					cnt++;
				}
			}
		}
		if (ans < cnt) ans = cnt;
	}
	if (!ans) ans = 1;
	cout << ans << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}