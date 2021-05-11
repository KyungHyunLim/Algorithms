/*
마법사 상어와 비바라기

1. 구름 이동
  - 불필요한 중복연산 최소화 (% 연산 사용으로 이동 횟수 최소화)
  - 경계 넘어가는 좌표 값 처리
  - 이동 후 동일하게 위치하는 구름 하나로 합치기 (Bool 배열 이용 중복 체크)
  
2. 물양 증가
  - 1의 결과로 얻은 구름 리스트를 이용한 반복문
  - 증가한 부분은 구름이 사라진 부분과 동일함으로 Bool 배열에 구름 사라짐 표시
  
3. 구름 제거
  - 4번 이후 처리
  
4. 물복사 버그
  - 구름 위치 = 물의 양이 증가한 바구니
  - 구름 위치에 대해 물복사 버그 -> 대각선 4방위 탐색
  - 경계가 넘어가는 것은 거리 1로 치지 않음으로 제외
  - 종료 후, 3번 처리(clouds.clear())
  
5. 구름 생성
  - 2번에서 표시한 Bool 배열 활용
  - 물의 양이 2 이상이고, 구름이 사라진 곳이 아니면 구름생성
  
6. 실행번호(idx) 증가, 1-6 - M번 반복

*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 맵크기
int N;
// 움직임 횟수
int M;

// 8방위 - 구름이동
int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

// 대각선 4방위 - 물의 양 증가(주변 바구니 탐색)
int dx_diagonal[4] = { -1,1,-1,1 };
int dy_diagonal[4] = { -1,-1,1,1 };

// 물의 양이 증가한 바구니 리스트
vector<pair<int, int>> increased;

// 구름이 사라진 위치 표시
bool disappear[51][51];

// 각 바구니의 물의 양 정보
int map[51][51];

// 이동 명령
vector<pair<int, int>> commands;

// 구름 이동
vector<pair<int, int>> Move(vector<pair<int, int>>& clouds, int idx) {
	int d = commands[idx].first;
	int mv = commands[idx].second % N;
	vector<pair<int, int>> new_clouds;
	bool temp[51][51];
	memset(temp, false, sizeof(temp));

	for (int i = 0; i < clouds.size(); i++) {
		// 구름 별 이 동후 좌표 설정
		clouds[i].first = clouds[i].first + (dx[d] * mv);
		if (clouds[i].first > N) clouds[i].first = clouds[i].first - N;
		else if (clouds[i].first < 1) clouds[i].first = clouds[i].first + N;

		clouds[i].second = clouds[i].second + (dy[d] * mv);
		if (clouds[i].second > N) clouds[i].second = clouds[i].second - N;
		else if (clouds[i].second < 1) clouds[i].second = clouds[i].second + N;
		
		// 겹친 구름 하나로 만들기
		if (!temp[clouds[i].first][clouds[i].second]) {
			temp[clouds[i].first][clouds[i].second] = true;
			new_clouds.push_back(make_pair(clouds[i].first, clouds[i].second));
		}
	}
	// 이동된 구름들 좌표 반환
	return new_clouds;
}

// 물복사 버그
void Bug(vector<pair<int, int>>& clouds) {
	for (int i = 0; i < clouds.size(); i++) {
		int x = clouds[i].first;
		int y = clouds[i].second;
		int iswater = 0;
		for (int j = 0; j < 4; j++) {
			int nx = x + dx_diagonal[j];
			int ny = y + dy_diagonal[j];
			if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
			if (map[nx][ny] > 0) iswater++;
		}
		map[x][y] += iswater;
	}
}

void Print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	// 맵크기 및 이동 횟수 설정
	cin >> N >> M;

	// 기본 물의 양 정보 입력
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	// 이동 명령 입력
	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		commands.push_back(make_pair(d, s));
	}

	vector<pair<int, int>> clouds;
	// 초기 구름
	clouds.push_back(make_pair(N, 1));
	clouds.push_back(make_pair(N, 2));
	clouds.push_back(make_pair(N-1, 1));
	clouds.push_back(make_pair(N-1, 2));
	int idx = 0;
	while (idx < M) {
		// 1. 이동
		clouds = Move(clouds, idx);
		
		//cout << idx+1 << endl;
		//cout << "구름 이동 후 " << clouds .size() << endl;
		//Print();
		
		memset(disappear, false, sizeof(disappear));
		// 2. 구름 있는 칸 물량 증가
		for (int i = 0; i < clouds.size(); i++) {
			map[clouds[i].first][clouds[i].second]++;
			disappear[clouds[i].first][clouds[i].second] = true;
		}

		//cout << "물량 증가후" << endl;
		//Print();

		// 3. 구름 사라짐 ( 나중에 처리)
		// 4. 2에서 물이 증가한 칸에 물복사 버그
		Bug(clouds);

		//cout << "물 복사 버그 사용 후" << endl;
		//Print();

		// 5. 바구니 물의 양이 2이상인 곳에서 모두 그름 생성, 물의 양 2 감소
		clouds.clear();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				// 물의 양이 2인 곳에, 구름이 사라졌던 칸이 아니면
				if (map[i][j] >= 2 && !disappear[i][j]) {
					// 구름생성
					clouds.push_back(make_pair(i, j));
					// 물양 감소
					map[i][j] -= 2;
				}
			}
		}

		//cout << "구름 생성 후" << endl;
		//Print();

		// 다음순서로 진행
		idx++;
	}

	// 6. 끝난 후 물의 양 계산
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			answer += map[i][j];
		}
	}

	cout << answer << endl;
	return 0;
}
