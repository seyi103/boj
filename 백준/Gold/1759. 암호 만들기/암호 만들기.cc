#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int L, C;
char s[15];
char path[15];
int visited[15];

void input() {
	cin >> L >> C;
	for (int i = 0; i < C; i++) {
		char tmp;
		cin >> tmp;
		s[i] = tmp;
	}
}

int check(string p) {
	int ccnt = 0, acnt = 0;
	for (int i = 0; i < L; i++) {
		if (p[i] == 'a' || p[i] == 'e' || p[i] == 'i' || p[i] == 'o' || p[i] == 'u')
			acnt++;
		else
			ccnt++;
	}
	if (acnt >= 1 && ccnt >= 2)
		return 1;
	return 0;
}

void dfs(int cnt, string path) {
	if (cnt == L) {
		if (path[0] == 0)
			return;
		if (check(path)) 
			cout << path << '\n';
		
		return;
	}
	for (int i = 0; i <= C; i++) {
		// 가지치기 -> 이미 사용 했으면 pass
		if (visited[i] == 1)
			continue;
		if (!path.empty() && path.back() > s[i]) 
			continue;
		
		visited[i] = 1; 
		path.push_back(s[i]);
		dfs(cnt + 1, path); 
		path.pop_back();
		visited[i] = 0; 
	}
}

void solve() {
	sort(s, s + C);
	dfs(0, "");
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}