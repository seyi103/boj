#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node {
	int to;
	int cnt;
};

int N, K;
int visited[200001];
int PREV[200001];
vector<int> path;

void bfs(int start) {
	queue<Node> q;
	q.push({ start, 0});

	visited[start] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		if (now.to == K) {
			cout << now.cnt << '\n';
			int idx = now.to;
			while (idx != N)
			{
				path.push_back(idx);
				idx = PREV[idx];
			}
			break;
		}

		int n1 = now.to + 1;
		if (n1 >= 0 && n1 <= 200000 && !visited[n1]) {
			visited[n1] = 1;
			PREV[n1] = now.to;
			q.push({ n1, now.cnt + 1});
		}
		int n2 = now.to - 1;
		if (n2 >= 0 && n2 <= 200000 && !visited[n2]) {
			visited[n2] = 1;
			PREV[n2] = now.to;
			q.push({ n2, now.cnt + 1});
		}
		int n3 = now.to * 2;
		if (n3 >= 0 && n3 <= 200000 && !visited[n3]) {
			visited[n3] = 1;
			PREV[n3] = now.to;
			q.push({ n3, now.cnt + 1});
		}
	}
}

int main() {
	fastIO;
	cin >> N >> K;
	if (N >= K) {
		cout << N - K << '\n';
		for (int i = N; i >= K; i--) 
			cout << i << ' ';
		cout << '\n';
	}
	else {
		bfs(N);
		cout << N << ' ';
		for (int i = path.size() - 1; i >= 0; i--)
			cout << path[i] << ' ';
	}
	return 0;
}