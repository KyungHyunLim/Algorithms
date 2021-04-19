/*
보호 필름

- 3개 핵심 기능
  1. 합격 판단 => 단순 반복문, 조건문
  2. 약물 투입 막 선택 => 조합
  3. 투입될 약물 선택(A, B) => 비트마스킹 
  (E.g 2개의 막에 약물을 투입하는 경우 00, 01, 10, 11 4가지)
*/

#include<iostream>

using namespace std;

// D: 두께
// W: 가로크기
// K: 합격기준
int D, W, K;

// 필름 DxW
int film[13][20];
int temp_film[13][20];

// 약물 투입수
int injection;
bool ok;

// 합격 유무 검사
bool check(int f[][20]) {
	// 모든 세로줄에 대해
	for (int i = 0; i < W; i++) {
		// K개가 필요함으로 D-K까지
		bool flag = true;
		for(int j=0; j<D-K+1; j++){
			// 현재 막 특성
			int base = f[j][i];
			flag = true;
			for (int z = 1; z < K; z++) {
				// base와 특성이 다르면 합격 불가
				if (base != f[j + z][i]) {
					flag = false;
					break;
				}
			}
			// 합격 기준 만족시 다음 세로줄로
			if (flag) break;
		}
		// 한 세로줄이 합격하지 못했으면
		if (!flag) return false;
	}
	// 모두 합격한 경우
	return true;
}

void combination(int arr[13], int n, int r, int next, int i) {
	// 이미 완료됬으면 모든 재귀함수 정리
	if (ok) return;
	if (i == r) {
		// 2. 투입할 막 조합 완성 A로 바꿀건지 B로 바꿀건지
		// eg, r = 2 => z = 00 01 10 11
		for (int z = 0; z < (1 << r); z++) {
			// Copy_map;
			for (int i = 0; i < D; i++) {
				for (int j = 0; j < W; j++) {
					temp_film[i][j] = film[i][j];
				}
			}
			// 선택된 막, 선택된 특성으로 변경
			// 0: A, 1: B
			for (int k = 0; k < r; k++) {
				// 해당 비트가 1이면 B로 변경
				if (z & (1 << k)) {
					for (int j = 0; j < W; j++) {
						temp_film[arr[k]][j] = 1;
					}
				}
				// 아니면 A로 변경
				else {
					for (int j = 0; j < W; j++) {
						temp_film[arr[k]][j] = 0;
					}
				}
			}
			// 3. 합격검사
			ok = check(temp_film);
			if (ok) break;
		}
		return;
	}
	if (next >= n) return;
	arr[i] = next;
	combination(arr, n, r, next + 1, i + 1); // 다음것 선택
	combination(arr, n, r, next + 1, i); // 다음것 선택 안함
}


int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int test_case;
	int T;
	
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> D >> W >> K;
		// 필름 정보 입력
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cin >> film[i][j];
			}
		}
		bool a = check(film);

		if (K == 1 || a) {
			cout << "#" << test_case << " 0" << endl;
			continue;
		}

		injection = 0;
		// 합격 할때까지
		while (true) {
			// 0. 약물 투입 수 증가
			injection++; 
			ok = false;

			// 1. 투입할 막 선택
			int arr[13];
			combination(arr, D, injection, 0, 0);
			if(ok) break;
		}

		cout << "#" << test_case << " " << injection << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
