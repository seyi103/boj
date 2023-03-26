#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ydir[] = { 0,-1,0,1 };
int xdir[] = { 1,0,-1,0 };
int ey, ex;

int MAP[101][101];
int N; // 드래곤 커브 개수
vector<int> dir;

void curve() {
	for (int i = dir.size() - 1; i >= 0; i--) {
		// 다음 방향을 구하고
		int d = (dir[i] + 1) % 4;
		// 다음 좌표 
		ey += ydir[d];
		ex += xdir[d];
		// 하나의 드래곤 커브를 그렸다!
		MAP[ey][ex] = 1;
		// 다음 방향을 담는다
		dir.push_back(d);
	}
}

int main() {
	fastIO;

	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;

		dir.clear();

		// 드래곤 커브의 시작점을 그리자
		MAP[y][x] = 1;
		// 0세대 드래곤 커브를 그려보자
		ex = x + xdir[d];
		ey = y + ydir[d];
		// 0세대 드래곤 커브를 그렸다!
		MAP[ey][ex] = 1;
		// 방향 정보 저장
		dir.push_back(d);
		// 이제 g세대 까지 드래곤 커브를 그려보자!
		for (int i = 0; i < g; i++)
			curve();
	}

	// 다 그렸으면 네 꼭짓점 모두 드래곤 커브인 개수를 찾자
	int cnt = 0;
	for (int i = 0; i <= 99; i++)
		for (int j = 0; j <= 99; j++)
			if (MAP[i][j] && MAP[i][j + 1] && MAP[i + 1][j] && MAP[i + 1][j + 1])
				cnt++;

	cout << cnt;

	return 0;
}
