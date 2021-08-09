#include<iostream>
#include<cstring>
using namespace std;

int N;
int length;
int cnt;

// N이 100만 => O(N) 알고리즘으로 풀어야 안전하다

void search(string P, string S) {
	for (int i = 0; i < S.length(); i++) {
		// 패턴이 이어지지 않아서 넘어온 것임으로 패턴 넘버 초기화
		int n = 0; // patter number
		if (S[i] == 'O') continue; //'O' 로 시작하면 패턴과 맞지 않음
		else {
			while (S[i + 1] == 'O' && S[i + 2] == 'I') {
				/* 
				I 에서 IOI 가 되면 n=1
				IOI 에서 IOIOI 가 되면 n=2
				*/
				n++;
				// 원하는 패턴과 동일하면
				if (n == N) {
					// 갯수 증가
					cnt++;
					// 맨앞 IO 제거
					n--;
				}
				// IO가 추가 됬음으로 2칸 이동
				i += 2;
			}
		}
	}
}

int main() {
	string base = "OI";
	string P = "IOI";
	string S;

	// 입력
	cin >> N;
	cin >> length;
	cin >> S;

	// 초기화
	cnt = 0;

	// 탐색
	search(P, S);

	cout << cnt << endl;

	return 0;
}
