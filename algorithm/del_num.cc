#include<iostream>
#include<string>
using namespace std;
string num;
void solve(int s, int k) {
	if (k == 0) return;
	int p = s;
	for (int i = s; i <= num.size() - k; ++i) {
		if (num[i] > num[p]) {
			p = i;
		}
	}
	cout << num[p];
	solve(p+1, k - 1);
}

int main () {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int k;
		cin >> num >> k;
		solve(0, num.size() - k);
		cout << endl;
	}
	return 0;
}
