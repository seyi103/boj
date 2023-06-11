#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
using namespace std;

int N;
int DAT[20];
int dialDAT1[30 - 2];
int dialDAT2[30 - 1];
int cnt;

void dfs(int now) {
	if (now == N) {
		cnt++;
		return;
	}
	for (int i = 0; i < N; i++) {
		if (DAT[i] + dialDAT1[now + i] + dialDAT2[N - (now - i)] == 0) {
			DAT[i] = 1;
			dialDAT1[now + i] = 1;
			dialDAT2[N - (now - i)] = 1;
			dfs(now + 1);
			DAT[i] = 0;
			dialDAT1[now + i] = 0;
			dialDAT2[N - (now - i)] = 0;
		}
	}
}

int main() {
	fastIO;
	cin >> N;
	dfs(0);
	cout << cnt << '\n';
	return 0;
}