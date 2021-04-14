/*
어른 상어

0. 
상어[M] = {위치, 방향, 우선순위 DB}
상어맵 = {상어번호} - 2에 사용
냄새맵 = {상어번호, 잔여기간} - 3 에 사용

1. 냄새 뿌리기
2. 상어이동 -> 핵심
  2-0. 임시 상어맵 생성
  2-1. 빈칸 찾기
  2-2. 없으면 자기 냄새가 있는 곳으로
  2-3. 겹치는 상어 제거
  2-4. 상어맵 - 임시 상어맵 swap
3. 냄새 잔여기간 조정
  3-1. k--
  3-2. k가 0이 되면 초기화
4. 1000초일 이상시 -1;

*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// N: 맵크기, M: 상어수, K: 냄새 잔여기간
int N, M, K;

// 상어 구조체
struct shark {
	int x, y; // 위치
	int d; // 방향
	int order[4][4]; // 방향 별 우선순위
};

struct smell{
	int n; // 냄새 주인 번호
	int k; // 유효기간
};
// 상어 정보
shark sharks[401];
int shark_map[20][20];

// 냄새 정보
smell smells_map[20][20];

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void Print() {
	cout << "상어맵 정보: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << shark_map[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "냄새맵 정보: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << smells_map[i][j].n << "(" << smells_map[i][j].k <<")" << "\t";
		}
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	// 상어 및 상어 맵 정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (temp != 0) {
				sharks[temp].x = i;
				sharks[temp].y = j;
				shark_map[i][j] = temp;
			}
		}
	}

	// 상어 방향 정보 입력
	for (int i = 1; i <= M; i++) {
		cin >> sharks[i].d;
	}

	// 상어 방향 별 우선순위 정보 입력
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> sharks[i].order[j][k];
			}
		}
	}

	// 상어 이동 시작
	int time = 0;
	int shark_count = M;
	while (true) {
		// 0-1. 상어가 한마리 밖에 없으면 종료
		if (shark_count == 1) break;
		// 0-2. 1000초가 넘어가면 종료
		if (time >= 1000){ time = -1; break;	}

		// 1. 냄새 뿌리기
		for (int i = 1; i <= M; i++) {
			if (sharks[i].d != -1) {
				smells_map[sharks[i].x][sharks[i].y].n = i;
				smells_map[sharks[i].x][sharks[i].y].k = K;
			}
		}

		//cout << "1. 냄새 뿌리기" << endl;
		//Print();

		// 2. 상어 이동
		int c_shark_map[20][20] = { 0 };
		for (int i = 1; i <= M; i++) {
			// 살아 있는 상어에 대해 진행
			if (sharks[i].d != -1) {
				// 현재 이동시킬 상어 정보
				int x = sharks[i].x;
				int y = sharks[i].y;
				int d = sharks[i].d - 1;

				bool flag = false;
				for (int j = 0; j < 4; j++) {
					// 우선순위 조건에 따른 다음 좌표
					int nx = x + dx[sharks[i].order[d][j]-1];
					int ny = y + dy[sharks[i].order[d][j]-1];

					// 맵 경계를 벗어나면 안됨
					if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
					// 빈칸이 아니면 안됨
					if (smells_map[nx][ny].n != 0) continue;
					// 이동 가능한 빈칸이 있으면
					flag = true;
					// 이동 칸의 상어가 자기보다 높은 번호면 상대 제거
					if (c_shark_map[nx][ny] > i || c_shark_map[nx][ny] == 0) {
						if (c_shark_map[nx][ny] != 0) shark_count--;
						sharks[c_shark_map[nx][ny]].d = -1; // 상대 제거
						c_shark_map[nx][ny] = i;
						sharks[i].x = nx;
						sharks[i].y = ny;
						sharks[i].d = sharks[i].order[d][j];
					}
					else { // 낮은 번호면 자신 제거
						sharks[i].d = -1;
						shark_count--;
					}
					break;
				}

				// 빈칸이 존재 하지 않음을 의미
				if (!flag) {
					for (int j = 0; j < 4; j++) {
						// 우선순위 조건에 따른 다음 좌표
						int nx = x + dx[sharks[i].order[d][j]-1];
						int ny = y + dy[sharks[i].order[d][j]-1];

						// 맵 경계를 벗어나면 안됨
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
						// 자기 자신의 냄새가 아니면 안됨
						if (smells_map[nx][ny].n != i) continue;
						// 자기 자신의 냄새가 있는 칸으로 이동
						c_shark_map[nx][ny] = i;
						sharks[i].x = nx;
						sharks[i].y = ny;
						sharks[i].d = sharks[i].order[d][j];					
						break;
					}
				}
			}
		}

		swap(shark_map, c_shark_map);
		//cout << "2. 상어이동" << endl;
		//Print();

		// 3. 냄새 잔여 기간 조정
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 냄새가 존재하면
				if (smells_map[i][j].n != 0) {
					smells_map[i][j].k--;
					// 잔여 기간 종료시 초기화
					if (smells_map[i][j].k == 0) {
						smells_map[i][j].n = 0;
					}
				}
			}
		}

		//cout << "3. 냄새 잔여 기간 조정" << endl;
		//Print();
		//cout << endl;

		// 4. 1초 증가
		time++;
	}

	cout << time << endl;

	return 0;
}
