#include <string>
#include <queue>
using namespace std;

struct Node {
	int idx;
	int p; // 중요도
};

priority_queue<int> pq;
queue<Node> q;

int solution(vector<int> priorities, int location) {
    int answer = 0;

	for (int i = 0; i < priorities.size(); i++) {
		int now = priorities[i];
		pq.push(now);
		q.push({ i, now });
	}
	int ord = 1;
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		int MAX = pq.top();
		if (now.p == MAX) {
			pq.pop();
			if (now.idx == location) {
				answer = ord;
				break;
			}
			ord++;
		}
		else {
			q.push(now);
		}
	}

	return answer;
}