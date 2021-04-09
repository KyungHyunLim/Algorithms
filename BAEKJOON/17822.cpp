/*
원판 돌리기

* 인접하고 동일한 숫자는 모두 지워야함
E.g [5,5,5,6] => [0,0,0,6] ([5,5,5,6] => [0,0,5,6] 으로 했다 고생...)

1. info 구조체 {숫자, 상태}
2. 원판 회전
  2-1. 배열 생성
  2-2. 생성된 배열에 회전 상태 입력 
    시계방향: temp[(j + k) % M] = circle[i][j];
    반시계방향: temp[(j + (M - k)) % M] = circle[i][j];
  2-3. 원래 배열에 업데이트
3. 인접 숫자제거
  3-1. 2중 for문 x2 (좌우 / 상하 관계)
    인접 및 숫자 동일하면 상태 false로 변경
    flag 값 토글
  3-2. 상태 false 처리된 항목 숫자 0 으로 변환
4. 제거된 숫자가 없으면
  4-1. 평균 구하기
  4-2. 조건에 따라 값 변경
5. 2-4 T회 반복
6. 원판에 남은 값 모두 더하기
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 원판의 한 숫자의 정보
// 값과 지워져있는지 없는지
struct info {
	int num;
	bool alive;
	info() {
		alive = true;
	}
	info(int _n, bool _a) : num(_n), alive(_a) {};
};
// N : 원판의 수
// M : 각 원판의 숫자 수
// T : 회전 횟수
int N, M, T, sum;
// 원판들
info circle[51][51];
// 회전 명령
int ins[50][3];

void rotation(int x, int d, int k) {
	for (int i = 0; i < N; i++) {
		info temp[51];
		// 원판 번호가 x의 배수이면
		if ((i + 1) % x == 0) {
			for (int j = 0; j < M; j++) {
				// 시계방향 회전
				if (d == 0) temp[(j + k) % M] = circle[i][j];
				// 반시계방향 회전
				else temp[(j + (M - k)) % M] = circle[i][j];
			}
			// 회전한 원판으로 갱신
			for (int j = 0; j < M; j++) {
				circle[i][j].num = temp[j].num;
				circle[i][j].alive = temp[j].alive;
			}
		}
	}
}

bool remove() {
	bool flag = false;
	// 좌우 체크 (순환)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 이미 지워진 숫자 pass
			if (circle[i][j].num == 0) continue;
			// 같으면 모두 비활성화(지우기)
			if (circle[i][j].num == circle[i][(j + 1) % M].num) {
				circle[i][j].alive = false;
				circle[i][(j + 1) % M].alive = false;
				flag = true;
			}
		}
	}
	// 상하 체크 (비순환)
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N-1; i++) {
			// 이미 지워진 숫자 pass
			if (circle[i][j].num == 0) continue;
			// 같으면 모두 비활성화(지우기)
			if (circle[i][j].num == circle[i + 1][j].num) {
				circle[i][j].alive = false;
				circle[i + 1][j].alive = false;
				flag = true;
			}
		}
	}
	// 죽은 숫자 없애기
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			// 비활성화 됬으면
			if (!circle[i][j].alive) {
				circle[i][j].num = 0;
			}
		}
	}
	return flag;
}

double Mean() {
	sum = 0;
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (circle[i][j].alive) {
				sum += circle[i][j].num;
				count++;
			}
		}
	}
	return (double)sum / (double)count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> T;

	// 초기 원판 상태 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> circle[i][j].num;
		}
	}

	// 회전 명령 입력
	for (int i = 0; i < T; i++) {
		cin >> ins[i][0] >> ins[i][1] >> ins[i][2];
	}

	// T번 회전
	for (int i = 0; i < T; i++) {
		// 번호가 x의 배수인 원판을 d방향으로 k칸 회전
		int x = ins[i][0];
		int d = ins[i][1];
		int k = ins[i][2];

		// 회전
		rotation(x, d, k);
		// 인접수 제거
		if (!remove()) { // 제거된 것이 없으면
			// 평균보다 큰수는 -1, 
			double m = Mean();
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					// 활성화된 숫자 중
					if (circle[i][j].alive) {
						if (circle[i][j].num == 0) continue;
						// 평균보다 작은수는 +1
						if (m > (double)circle[i][j].num) {
							circle[i][j].num++;
						}
						// 평균보다 큰수는 -1
						else if (m < (double)circle[i][j].num) {
							circle[i][j].num--;
						}
					}
				}
			}
		}
	}

	// 원판에 적힌 수의 합
	Mean();
	cout << sum << endl; 

	return 0;
}
