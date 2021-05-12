/*
게리맨더링 2

완전탐색, 조건 구현이 까다로운 문제.
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MIN(A,B) A<B?A:B

// 맵크기 NxN
int N;
// 각 구역 인구수
int population[21][21];

// 선거구 별 인구수 계산
int calc(int x, int y, int d1, int d2) {
	// 각 선거구 인구수 저장
	vector<int> peoples(5,0);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// 1번 선거구
			if (i < x + d1 && j <= y && !(i >= x && j >= y - (i - x))) {
				peoples[0] += population[i][j];
			}
			// 2번 선거구
			else if (i <= x + d2 && j > y && !(i >= x && j <= y + (i - x))) {
				peoples[1] += population[i][j];
			}
			// 3번 선거구
			else if (i >= x + d1 && j < y-d1+d2 && 
				!(i <= x + d1 + d2 && j >= (y - d1 + d2 - (x + d1 + d2 - i)))) {
				peoples[2] += population[i][j];
			}
			// 4번 선거구
			else if (i > x + d2 && j >= y - d1 + d2 && 
				!(i <= x + d1 + d2 && j <= (y - d1 + d2 + (x + d1 + d2 - i)))) {
				peoples[3] += population[i][j];
			}
			else {
				peoples[4] += population[i][j];
			}
		}
	}
	sort(peoples.begin(), peoples.end());
	return peoples[4] - peoples[0];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	// 각 구역 인구수 입력
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> population[i][j];
		}
	}

	// 선거구 나누기 위한 변수들
	int x, y, d1, d2;
	int ans = 987654321;
	for (x = 1; x <= N - 2; x++) { // x 선택
		for (y = 1; y <= N - 2; y++) { // y 선택
			for (d1 = 1; d1 <= y - 1 && d1 <= N - x - 1; d1++) { // d1 선택
				for (d2 = 1; d2 <= N - y && d2 <= N - x - 1; d2++) { // d2 선택
					// 선거구 나누기 및 최소값 비교, 업데이트
					ans = MIN(ans, calc(x, y, d1, d2));
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
