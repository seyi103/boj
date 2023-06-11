#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
using namespace std;

int N;
int DAT[20];
int cnt;

void dfs(int now) {
	if (now == N) {
		cnt++;
		return;
	}
	for (int i = 0; i < N; i++) {
		DAT[now] = i;
		int flag = 0;
		for (int j = 0; j < now; j++) {
			if (DAT[now] == DAT[j]) {
				flag = 1;
				break;
			}
			else if (abs(DAT[now] - DAT[j]) == now - j) {
				flag = 1;
				break;
			}
		}
		if (!flag)
			dfs(now + 1);
		DAT[now] = 0;
	}
}

int main() {
	fastIO;
	cin >> N;
	dfs(0);
	cout << cnt << '\n';
	return 0;
}