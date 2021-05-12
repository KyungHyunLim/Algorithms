#define _CRT_SECURE_NO_WARNINGS

#define MIN(A,B) A<B?A:B
#define ll long long

#include <iostream>
#include <cstring>
#include <queue>
#include <string.h>
#include <set>

using namespace std;

ll start, target;
bool flag;
string signs[4] = { "*", "+", "-", "/" };

ll calc(int sign, ll num) {
	if (sign == 1) return num + num;
	else if (sign == 2) return num - num;
	else if (sign == 0) return num * num;
	else return num / num;
}

string solve(){
	queue<pair<ll, string>> q;
	q.push(make_pair(start, ""));

	set<ll> check;

	while (!q.empty()) {
		ll now_n = q.front().first;
		string now_s = q.front().second;
		q.pop();

		if (now_n == target) {
			flag = true;
			return now_s;
		}

		for (int i = 0; i < 4; i++) {
			ll new_n = calc(i, now_n);
			if (new_n < 1) continue;
			if (check.find(new_n) != check.end()) continue;
			check.insert(new_n);
			string new_s = now_s + signs[i];
			q.push(make_pair(new_n, new_s));
		}
	}
	return "a";
}

int main() {
	
	cin >> start >> target;

	if (start == target) { cout << 0;  return 0; }

	flag = false;
	string answer = solve();

	if (flag) cout << answer;
	else cout << -1;
	
	return 0;
}
