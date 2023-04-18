#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

// bfs로 탐색하며 연합의 번호 붙임
// 다시 bfs 탐색하며 인구수 이동

struct Node {
	int y, x;
};

struct Country {
	int area;
	int sum;
};

int ydir[] = { 1,-1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, L, R;
int MAP[51][51];
int COPY[51][51];

int check[51][51];
int visited[51][51];

unordered_map<int, Country> um;
int SIZE;

void input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			
		}
	}
}

void init() {
	memset(check, 0, sizeof(check));
	memset(visited, 0, sizeof(visited));
}

bool isOpen(int diff) {
	return diff >= L && diff <= R;
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

Country getDiff(int y, int x, int num) {
	queue<Node> q;
	q.push({ y, x });

	visited[y][x] = 1;
	check[y][x] = num;

	int area = 1;
	int sum = MAP[y][x];

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx])
				continue;
			int diff = abs(MAP[now.y][now.x] - MAP[ny][nx]);
			if (!isOpen(diff))
				continue;

			area++;
			sum += MAP[ny][nx];

			check[ny][nx] = num;
			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	return { area, sum };
}

// 연합을 만들자
int makeA() {
	init();
	int num = 1;
	int flag = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j])
				continue;
			Country tmp = getDiff(i, j, num);
			um[num] = tmp;
			num++;
			if (tmp.area != 1) {
				flag = 1;
			}
		}
	}
	SIZE = num;
	int de = 1;
	return flag;
}

void MOVE(int y, int x, int val) {
	memcpy(COPY, MAP, sizeof(MAP));

	queue<Node> q;
	q.push({ y,x });

	COPY[y][x] = val;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx])
				continue;
			if (check[ny][nx] != check[y][x])
				continue;

			visited[ny][nx] = 1;
			COPY[ny][nx] = val;
			q.push({ ny, nx });
		}
	}
	memcpy(MAP, COPY, sizeof(MAP));
}

// 이제 인구수 이동
void movepp() {
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j] && !visited[i][j]) {
				int idx = check[i][j];
				Country now = um[idx];
				if (now.area == 1)
					continue;
				int val = now.sum / now.area;
				MOVE(i, j, val);
			}
		}
	}
}

void solve() {
	int day = 0;
	while (true)
	{
		int flag = makeA();
		if (!flag)
			break;
		movepp();
		day++;
	}
	cout << day << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
