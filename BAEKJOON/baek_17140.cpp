/*
이차원 배열과 연산

1. 연산
  1-1. 카운팅 소트 (빈도수 정보 get)
  1-2. 퀵 소트     (빈도수-숫자 중요도로 정렬, 오름차순)
2. A에 대입
  2-0. 입력 행/열 초기화
  2-1. 숫자 - 빈도 순으로 A에 입력
  2-2. MAX 행/열 크기 업데이트
3. 시간 증가
4. 1-3 반복
  4-1. 100초가 지나면 break
  4-2. A[r][c]가 원하는 값이면 종료
*/
#define _CRT_NO_SECURE_WARNINGS_
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

#define MAX(A, B) A>B?A:B

// 초기 배열 크기 3x3
// R, C 원하는 값 위치
// K: 원하는 값
int R, C, K;

// A 배열, A[1]: 1행 - 1열 ~ 100열
int A[101][101];
int max_R, max_C;
// counting sort를 위한 배열
int _count[101];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C >> K;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> A[i][j];
		}
	}
	max_R = 3;
	max_C = 3;
	// 원하는 곳이 K가 될때 까지 반복
	int time = 0;
	while (A[R][C] != K) {
		// 100초가 지나면 -1
		if (time > 100) {
			time = -1;
			break;
		}

		// R연산
		int tem_max = 0;
		if (max_R >= max_C) {
			// 모든 행에 대해서
			for (int i = 1; i <= max_R; i++) {
				// Counting sort
				memset(_count, 0, sizeof(_count));
				for (int j = 1; j <= max_C; j++) _count[A[i][j]]++;

				// 빈도수 - 숫자 페어 정보 생성
				vector<pair<int, int>> info;
				for (int j = 1; j <= 100; j++) {
					if (_count[j] != 0) info.push_back(make_pair(_count[j], j));
				}

				// 정렬 빈도수가 낮고, 숫자가 작을 수록 앞으로
				sort(info.begin(), info.end());

				// 배열에 정보 업데이트
				for (int j = 1; j <= max_C; j++) A[i][j] = 0;
				int idx = 1;
				for (int k = 0; k < info.size(); k++) {
					A[i][idx++] = info[k].second;
					A[i][idx++] = info[k].first;
				}
				tem_max = MAX(tem_max, idx - 1);
			}
			max_C = tem_max;
		}
		// C연산
		else {
			// 모든 열에 대해서
			for (int i = 1; i <= max_C; i++) {
				// Counting sort
				memset(_count, 0, sizeof(_count));
				for (int j = 1; j <= max_R; j++) _count[A[j][i]]++;

				// 빈도수 - 숫자 페어 정보 생성
				vector<pair<int, int>> info;
				for (int j = 1; j <= 100; j++) {
					if (_count[j] != 0) info.push_back(make_pair(_count[j], j));
				}

				// 정렬 빈도수가 낮고, 숫자가 작을 수록 앞으로
				sort(info.begin(), info.end());

				// 배열에 정보 업데이트
				for (int j = 1; j <= max_R; j++) A[j][i] = 0;
				int idx = 1;
				for (int k = 0; k < info.size(); k++) {
					A[idx++][i] = info[k].second;
					A[idx++][i] = info[k].first;
				}
				tem_max = MAX(tem_max, idx - 1);
			}
			max_R = tem_max;
		}
		time++;
	}

	cout << time << endl;

	return 0;
}
