#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

struct Stack {
	int arr[100000];
	int idx;

	void init() {
		idx = -1;
	}

	void push(int data) {
		arr[++idx] = data;
	}

	bool empty() {
		return idx < 0;
	}

	int pop() {
		if (empty())
			return -1;
		return arr[idx--];
	}

	int size() {
		if (empty())
			return 0;
		return idx + 1;
	}

	int top() {
		if (empty())
			return -1;
		return arr[idx];
	}
};

int main() {
	int qry_cnt;
	scanf("%d", &qry_cnt);

	Stack stmp;
	stmp.init();

	for (int q = 0; q < qry_cnt; q++) {
		string qry;
		int data = 0, res = 0;
		int de = 1;
		cin >> qry;
		if (qry == "push") {
			scanf("%d", &data);
			stmp.push(data);
		}
		else if (qry == "pop") {
			res = stmp.pop();
			printf("%d\n", res);
		}
		else if (qry == "size") {
			res = stmp.size();
			printf("%d\n", res);
		}
		else if (qry == "empty") {
			res = stmp.empty();
			printf("%d\n", res);
		}
		else if (qry == "top") {
			res = stmp.top();
			printf("%d\n", res);
		}
	}
	return 0;
}