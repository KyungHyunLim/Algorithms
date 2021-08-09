#include<iostream>
#include<regex>
#include<cstring>

using namespace std;

bool isit(string str) {
	// 정규식 표현 정의
	regex expr("((100+1+)|(01))+");
	// 비교
	return regex_match(str, expr);
}


int main() {
	int N;
	cin >> N;

	// N 번 반복
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		cout << (isit(s) ? "YES" : "NO");
		cout << endl;
	}

	return 0;
}
