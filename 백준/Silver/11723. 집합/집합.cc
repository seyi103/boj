#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
using namespace std;

int M;
int n, i;

int main() {
	fastIO;

	string qry;
	cin >> M;
	for (int m = 0; m < M; m++) {
		cin >> qry;

		if (qry == "add") {
			cin >> n;
			i |= (1 << n);
		}
		else if (qry == "remove") {
			cin >> n;
			i &= ~(1 << n);
		}
		else if (qry == "check") {
			cin >> n;
			if (i & (1 << n)) cout << 1 << '\n';
			else cout << 0 << '\n';
		}
		else if (qry == "toggle") {
			cin >> n;
			i ^= (1 << n);
		}
		else if (qry == "all") 
			i = (1 << 21) - 1;
		else 
			i = 0;
	}

	return 0;
}