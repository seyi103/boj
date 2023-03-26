#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int tgt;
int M;
int DAT[10];

int main() {
	fastIO;
	cin >> tgt;
	string tmp = to_string(tgt);
	cin >> M;
	for (int i = 0; i < M; i++) {
		int n;
		cin >> n;
		DAT[n] = 1;
	}
	if (tgt == 100)
		cout << 0 << '\n';
	else {
		// solve -> 채널을 하나씩 올리면서 확인
		int MIN = abs(tgt-100), flag = 0;
		for (int i = 0; i <= 1000000; i++) {
			string tmp = to_string(i);
			flag = 0;
			for (int j = 0; j < tmp.length(); j++)
				// 현재 채널이 고장난 채널이면 break 
				if (DAT[tmp[j] - '0']) {
					flag = 1;
					break;
				}
			// 현재 채널이 고장난 채널이 포함되어 있으면 continue
			if (flag) continue;

			int cnt = abs(tgt - i) + tmp.length();
			if (cnt < MIN)
				MIN = cnt;
		}
		cout << MIN << '\n';
	}
	
	return 0;
}