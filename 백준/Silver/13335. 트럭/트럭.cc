#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <unordered_map>
using namespace std;

struct Truck {
	int idx;
	int w;
};

int N, blen, MAX_W;
queue<Truck> bridge, truck;
unordered_map<int, int> um;

void input() {
	scanf("%d %d %d", &N, &blen, &MAX_W);
	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		truck.push({ i, tmp });
		um[i] = 0;
	}
}

void solve() {
	int time = 0, weight = 0;
	while (1) {
		time++;
		int de = 1;
		// 다리를 다 건넜으면 빼준다
		queue<Truck> tmp;
		while (!bridge.empty()) {
			Truck now = bridge.front();
			bridge.pop();
			um[now.idx]++;
			if (um[now.idx] == blen) {
				weight -= now.w;
			}
			else {
				tmp.push(now);
			}
		}
		while (!tmp.empty()) {
			Truck now = tmp.front();
			tmp.pop();
			bridge.push(now);
		}
		// 이미 무게가 최대 하중 이상이면 continue
		if (weight > MAX_W)
			continue;
		// 다리를 건너기 시작
		if (!truck.empty()) {
			Truck now = truck.front();

			if (weight + now.w > MAX_W)
				continue;

			truck.pop();
			bridge.push(now);
			weight += now.w;
		}
		// 모두 다리를 건너면 종료
		if (bridge.empty() && truck.empty())
			break;
	}
	printf("%d\n", time);
}

int main() {
	input();
	solve();
	return 0;
}