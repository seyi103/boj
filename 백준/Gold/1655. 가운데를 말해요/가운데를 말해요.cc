#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

int N;
priority_queue<int> mxpq;
priority_queue<int, vector<int>, greater<int>> minpq;

int main() {
	//freopen("input.txt", "r", stdin);
	fastIO;

	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (mxpq.size() == minpq.size())
			mxpq.push(num);
		else
			minpq.push(num);

		if (!mxpq.empty() && !minpq.empty()) {
			if (mxpq.top() > minpq.top()) {
				int MAX, MIN;
				MAX = mxpq.top();
				mxpq.pop();

				MIN = minpq.top();
				minpq.pop();

				mxpq.push(MIN);
				minpq.push(MAX);
			}
		}
		cout << mxpq.top() << '\n';
	}

	return 0;
}