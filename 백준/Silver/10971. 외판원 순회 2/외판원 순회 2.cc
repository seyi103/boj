#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;

int N;
int MAP[11][11];
int visited[11];
int ans = 21e8;
int st;

void dfs(int now, int sum, int cnt) {
	// 기저조건 -> 시작 노드로 돌아왔고, 모든 노드를 방문 했다면
	if (cnt == N && now == st) {
		if (sum < ans)
			ans = sum;
		return;
	}
	
	// 재귀 구성
	for (int next= 0; next < N; next++) {
		if (visited[next])
			continue;
		if (!MAP[now][next])
			continue;
		// 가지치기 -> 내가 가진 값보다 크다면 가망 없는 길
		if (sum + MAP[now][next] > ans)
			continue;
		visited[next] = 1;
		dfs(next, sum + MAP[now][next], cnt + 1);
		visited[next] = 0;
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &MAP[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		st = i;
		dfs(i, 0, 0);
	}
	printf("%d\n", ans);
	return 0;
}