/*
마법사 상어와 블리자드

1. 사전 준비
  - map을 이용한 블럭순서 - 좌표 맵핑 (x,y) == (info[블럭번호].first, info[블럭번호].second)
  - 블리자드 시전 블럭 번호 (상 하 좌 우) => A[x] = A[x-1] + (A[x-1] - A[x-2] + 8)

2. 블리자드 사용
  - 1에서 준비한 info를 사용해 해당되는 블록번호의 좌표 0으로 변경
  
3. 빈칸 제거
  - 새로운 배열을 이용해 0을 제외 하고 옮기기
  
4. 구슬 폭파
  - flag 변수를 활용 폭팔이 없을때 까지 반복
  - beeds와 new_beeds를 스위칭 하며, 최신 상태를 저장
  - 4개 이상 연속하는 구슬들은 0으로 변경
  - 3번의 빈칸 제거 사용 (이때 새로운 배열은 beeds와 new_beeds중 최신화 상태를 담지 않은 배열)
  
5. 구슬 생성
  - new_beeds를 최신화 상태로 변경 (다음 iteration에 beeds를 최신화 상태배열로 사용하기 위함)
  - new_beeds를 하나씩 읽으며, count와 구슬번호를 블록순서에 맞추어 차례대로 beeds에 입력
  - 다 못채웠을 경우 나머지는 0으로 설정

6. 2 - 5 M회 반복


*/
#define _CRT_NO_SECURE_WARNINGS
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

// 맵크기
int N;
int max_size;
// 블리자드 시전 횟수
int M;
// 블리자드 시전 정보
vector<pair<int, int>> blizards;

// 칸 번호 - 좌표 매칭
map<int, pair<int, int>> info;

// ↑, ↓, ←, →
vector<int> d[5];

// ← ↓ → ↑
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

int destroyed[4];

void copy(int a[][51], int b[][51]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = b[i][j];
		}
	}
}

// 디버깅용
void Print(int a[][51]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

// 블리자드사용
void Using_blizard(int beeds[][51], int idx) {
	int direction = blizards[idx].first;
	int power = blizards[idx].second;
	for (int i = 0; i < power; i++) {
		//destroyed[beeds[info[d[direction][i]].first][info[d[direction][i]].second]]++;
		beeds[info[d[direction][i]].first][info[d[direction][i]].second] = 0;
	}
}

// 빈칸 제거
void Remove_empty(int beeds[][51], int new_beeds[][51]) {
	new_beeds[N / 2][N / 2] = -1;
	// 0으로 표시된 리스트에서 구슬 제거
	int temp_idx = 1;
	for (int i = 1; i < N * N; i++) {
		if (beeds[info[i].first][info[i].second] != 0) {
			new_beeds[info[temp_idx].first][info[temp_idx].second] = beeds[info[i].first][info[i].second];
			temp_idx++;
		}
	}
	for (int i = temp_idx; i < N * N; i++) {
		new_beeds[info[i].first][info[i].second] = 0;
	}
	//copy(beeds, new_beeds);
}

// 구슬폭파
bool Bomb(int beeds[][51]) {
	bool flag = true;
	for (int i = 1; i < N * N; i++) {
		// 현재 구슬 번호
		int cur = beeds[info[i].first][info[i].second];
		if (cur == 0) break;
		int count = 1;
		// 이후 구슬 확인
		for (int j = i + 1; j < N * N; j++) {
			if (cur != beeds[info[j].first][info[j].second]) break;
			count++;
		}
		// 연속된 구슬이 4개 이상이면 폭파시키기
		if (count >= 4) {
			flag = false;
			for (int j = 0; j < count; j++) {
				destroyed[cur]++;
				// 폭파 시키기
				beeds[info[i + j].first][info[i + j].second] = 0;
			}
			i += (count-1); // i + count 번째 까지는 터졌으니까 그 다음으로 이동
		}
	}
	return flag;
}

// 구슬 생성
void Make_beeds(int beeds[][51], int new_beeds[][51]) {
	int beeds_idx = 1;
	for (int i = 1; i < N * N; i++) {
		if (beeds_idx >= N * N) break;
		// 현재 구슬 번호
		int cur = new_beeds[info[i].first][info[i].second];
		// 폭파된 구슬 넘어가기
		if (cur == 0) continue;
		int count = 1;
		// 이후 3구슬 확인 (4개이상은 다 폭파됬으니까)
		for (int j = 1; j < 3; j++) {
			if (cur != new_beeds[info[i + j].first][info[i + j].second]) break;
			count++;
		}
		//printf("Cur: %d, 좌표(%d, %d), 개수: %d, 번호: %d\n", cur, info[i].first, info[i].second, count, beeds_idx);
		// 현재 구슬 번호 개수
		beeds[info[beeds_idx].first][info[beeds_idx].second] = count;
		beeds_idx++;
		if (beeds_idx >= N * N) break;
		// 현재 구슬 번호
		beeds[info[beeds_idx].first][info[beeds_idx].second] = cur;
		beeds_idx++;
		if (count > 1) i += (count-1);
	}
	// 끝까지 안채워 졌으면 나머지 0으로 채우기
	if (beeds_idx < N * N) {
		for (int s = beeds_idx; s <= N * N; s++) {
			beeds[info[s].first][info[s].second] = 0;
		}
	}

	//cout << endl;
	//cout << endl;

}

int main() {
	// 전체 구슬 정보
	int beeds[51][51];
	int new_beeds[51][51];

	memset(destroyed, 0, sizeof(destroyed));

	cin >> N >> M;
	max_size = N * N;

	// 블리 자드 시전 위치 사전 조사
	// ↑, ↓, ←, →
	d[1].push_back(7);
	d[1].push_back(22);
	d[2].push_back(3);
	d[2].push_back(14);
	d[3].push_back(1);
	d[3].push_back(10);
	d[4].push_back(5);
	d[4].push_back(18);
	int idx = 2;
	while (true) {
		d[1].push_back(d[1][idx - 1] + (d[1][idx - 1] - d[1][idx - 2] + 8));
		if (d[2][idx - 1] + (d[2][idx - 2] - d[1][idx - 1] + 8) > 2041) break;
		d[2].push_back(d[2][idx - 1] + (d[2][idx - 1] - d[2][idx - 2] + 8));
		d[3].push_back(d[3][idx - 1] + (d[3][idx - 1] - d[3][idx - 2] + 8));
		d[4].push_back(d[4][idx - 1] + (d[4][idx - 1] - d[4][idx - 2] + 8));
		idx++;
	}

	// 구슬 맵 정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> beeds[i][j];
		}
	}

	// 구슬 맵 정보 리스트로 변환
	int sx = N / 2;
	int sy = N / 2;
	beeds[sx][sy] = -1;
	info[0] = make_pair(sx, sy); // 상어
	// 달팽이 모양 이동
	int len = 1;
	int dir = 0;
	int sequence = 1;
	while (true) {
		if (sx == 0 && sy == 0) break;
		for (int i = 0; i < len; i++) {
			//cout << sx << " " << sy << endl;
			if (sx == 0 && sy == 0) break;
			sx += dx[dir];
			sy += dy[dir];
			info[sequence++] = make_pair(sx, sy);
		}
		dir = (dir + 1) % 4;
		if (dir % 2 == 0) len++;
	}


	// 블리자드 시전 정보 입력
	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		blizards.push_back(make_pair(d, s));
	}

	idx = 0;
	
	while (idx < M) {
		//cout << "초기: " << idx << endl;
		//Print(beeds);

		// 1. 블리자드 시전
		Using_blizard(beeds, idx);

		//cout << "블리자드 시전 후: " << idx << endl;
		//Print(beeds);
		
		// 2. 빈칸 제거
			// 뒤의 배열이 최신 상태
		Remove_empty(beeds, new_beeds);
		
		//cout << "블리자드 파편 청소 후: " << idx << endl;
		//Print(new_beeds);

		// 3. 구슬 폭파
			// 앞의 배열이 최신상태
		int turn = 0;
		while (true) {
			if (turn % 2 == 0) {
				if (!Bomb(new_beeds)) {
					//cout << "구슬 폭파: " << idx << " " << turn << endl;
					//Print(new_beeds);

					// 빈칸 제거 - beeds가 최신
					Remove_empty(new_beeds, beeds);

					//cout << "구슬 폭파 후 청소: " << idx << " " << turn << endl;
					//Print(beeds);
				}
				else break;
			}
			else {
				if (!Bomb(beeds)) {
					//cout << "구슬 폭파: " << idx << " " << turn << endl;
					//Print(beeds);

					// 빈칸 제거 - new_beeds가 최신
					Remove_empty(beeds, new_beeds);

					//cout << "구슬 폭파 후 청소: " << idx << " " << turn << endl;
					//Print(new_beeds);
				}
				else break;
			}
			turn++;
		}
		
			
		// 4. 구슬 생성
		//최신 상태를 new_beeds 배열로 갱신
		if (turn % 2 != 0) copy(new_beeds, beeds);
		Make_beeds(beeds, new_beeds);
		
		//cout << "구슬 생성 후: " << idx << endl;
		//Print(beeds);
	
		idx++;
	}
	int answer = 0;

	//cout << endl;
	//for (int i = 1; i < 4; i++) cout << destroyed[i] << "\t";
	//cout << endl;

	answer = 1 * destroyed[1] + 2 * destroyed[2] + 3 * destroyed[3];
	cout << answer << endl;

	return 0;
}
