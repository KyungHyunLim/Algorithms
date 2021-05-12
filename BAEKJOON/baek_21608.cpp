/*
상어초등학교

- 문제에서 제시하는 조건 구현

1. 학생 순서에 따라
2. 좌석별 정보 파악( 선호학생수, 빈 자리수, 행좌표, 열좌표)
3. 2에서 구한 좌석 정렬 -> 최적의 후보 선택(index - 0번)
4. 1-3 반복 (학생들이 모두 앉을 때 까지)
5. 맵순회하며 주변 선호 학생수에 따라 

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include <cstring>

using namespace std;

// 맵크기
int N;	
// 학생의 선호도 정보
vector<int> student[401];
vector<int> list;
int map[21][21];

// 좌석의 정보 구조체
// 좌석 배치 기준, 선호학생 수, 빈 자리, 행좌표, 열좌표
struct seat {
	int x, y;
	int n_empty = 0;
	int n_prefer = 0;
};

// 선호학생 수, 빈 자리, 행좌표, 열좌표 순 정렬
bool comp(seat a, seat b) {
	if (a.n_prefer > b.n_prefer) return true;
	else if (a.n_prefer == b.n_prefer) {
		if (a.n_empty > b.n_empty) return true;
		else if(a.n_empty == b.n_empty){
			if (a.x < b.x) return true;
			else if(a.x == b.x) {
				if (a.y < b.y) return true;
				else return false;
			}
		}
	}
	return false;
}

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

// 선호학생수에 따른 점수 변환
int calc(int a) {
	if (a == 4) return 1000;
	else if (a == 3) return 100;
	else if (a == 2) return 10;
	else if (a == 1) return 1;
	else return 0;
}

int main() {

	cin >> N;
	memset(map, 0, sizeof(map));

	// 학생 자리 배치 순서 및 학생 선호도 정보 입력
	for (int i = 0; i < N * N; i++) {
		int st_num;
		cin >> st_num;
		// 학생 자리 배치 순서
		list.push_back(st_num);
		for (int j = 0; j < 4; j++) {
			int temp;
			cin >> temp;
			// 학생 선호도 정보
			student[st_num].push_back(temp);
		}
	}

	// 자리 배치
	for (int i = 0; i < list.size(); i++) {
		// 처음이면 1,1에 자리
		if (i == 0) {
			map[1][1] = list[0];
		}
		// 처음이 아니면
		else {
			// 좌석정보
			vector<seat> candidates;
			int cur_student = list[i];

			// 한칸한칸 좌석 확인해 정보 채우기
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					// 이미 앉은 좌석은 후보가 될수 없음
					if (map[j][k] != 0) continue;

					// 현재 좌표
					int cur_x = j;
					int cur_y = k;

					// 선호도 정보
					int prefer = 0;
					for (int z = 0; z < 4; z++) {
						int nx = cur_x + dx[z];
						int ny = cur_y + dy[z];
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
						if (map[nx][ny] == 0) continue;
						for (int t = 0; t < 4; t++) {
							if (student[cur_student][t] == map[nx][ny]) {
								prefer++;
								break;
							}
						}
					}

					// 빈칸 정보
					int empty = 0;
					for (int z = 0; z < 4; z++) {
						int nx = cur_x + dx[z];
						int ny = cur_y + dy[z];
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
						if (map[nx][ny] != 0) continue;
						empty++;
					}

					// 정보 입력
					seat temp;
					temp.x = j;
					temp.y = k;
					temp.n_empty = empty;
					temp.n_prefer = prefer;
					candidates.push_back(temp);
				}
			}
			// 기준에 맞추어 정렬
			if (candidates.size() > 0) {
				sort(candidates.begin(), candidates.end(), comp);
				map[candidates[0].x][candidates[0].y] = cur_student;
			}
		}
	}

	// 점수 계산
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int cur_student = map[i][j];
			int cur_x = i;
			int cur_y = j;
			int pre = 0;
			for (int k = 0; k < 4; k++) {
				int nx = cur_x + dx[k];
				int ny = cur_y + dy[k];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				for (int t = 0; t < 4; t++) {
					if (student[cur_student][t] == map[nx][ny]) {
						pre++;
						break;
					}
				}
			}
			answer += calc(pre);
		}
	}
	cout << answer << endl;

	return 0;
}
