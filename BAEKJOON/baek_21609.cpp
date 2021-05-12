/*
상어중학교

4단계 구현

1단계 - 가장 큰 보석찾기
  1. BFS로 같은 색, 무지개색 보석 탐색
    - 탐색을 통해 크기, 경로(전체, 무지개 제외), 무지개색 보석 수 구하기
    - 조건에 따라 가장 큰 보석 변경
    - 남아있는 보석 덩어리가 없으면 종료
    
2단계 - 보석제거
    - 1단계에서 얻은 Block 구조체의 path 정보를 따라 빈칸(-2)으로 변경

3단계 - 중력작용
    - 열순, 행끝~처음 순 탐색
    - 빈칸이면 빈칸이 아닐때 까지 이동해 값 Swap,
    - 만약 검은 돌이면 Swap 하지 않고 넘어가기

4단계 - 회전
    - 큰 사각형 부터 순차 회전

5단계 - 3단계와 동일

*/
#define _CRT_NO_SECURE_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

// NxN 맵크기
// M 원석 색상 종류
	// -1: 검은색 블록, 0: 무지개 블록, 1~M: 색상블록
int N, M;
bool visited[20][20]; // 가장 큰 블럭 탐색용
int map[20][20]; // 맵정보
int MAX_size;	// 가장 큰 블럭 크기

// 블럭 정보
struct Block {
	int x, y;
	int n_rainbow;
	vector<pair<int, int>> path;
	Block() {};
	Block(int x, int y, int n_rainbow) : x(x), y(y), n_rainbow(n_rainbow) { path.clear(); };
};
Block big;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

bool path_sorting(pair<int,int> a, pair<int,int> b) {
	if (a.first < b.first) return true;
	else if (a.first == b.first) {
		if (a.second < b.second) return true;
	}
	return false;
}

// 가장 큰 블럭 탐색
void Bfs(int x, int y, int c) {
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;
	int temp_size = 1; // 시작점 보석

	// 무지개는 방문 표시 해제 필요
	vector<pair<int, int>> rainbow;
	// 블록 삭제를 위한 경로 저장
	vector<pair<int, int>> path;
	// 보석 기준 지점을 위한 경로 저장
	vector<pair<int, int>> Ex_rainbow_path;
	Ex_rainbow_path.push_back(make_pair(x, y));
	path.push_back(make_pair(x, y));
	while (!q.empty()) {
		// 현재 좌표
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		// 주변 탐색
		for (int i = 0; i < 4; i++) {
			// 주변 좌표
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			// 맵 밖으로 나가면 안됨
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			// 이미 방문했거나, 빈칸이거나, 검은색이면 처리할 필요 없음 
			if (visited[nx][ny] || map[nx][ny] == -2 || map[nx][ny] == -1) continue;
			// 같은 색상이거나 무지개 색상이면 진행
			if (map[nx][ny] == c || map[nx][ny] == 0) {
				// 무지개 색상이면 나중에 초기화를 위해 좌표 저장
				if (map[nx][ny] == 0) rainbow.push_back(make_pair(nx, ny));
				if (map[nx][ny] != 0) Ex_rainbow_path.push_back(make_pair(nx, ny));
				path.push_back(make_pair(nx, ny));
				// 방문표시
				visited[nx][ny] = true;
				// 크기증가
				temp_size++;
				q.push(make_pair(nx, ny));
			}
		}
	}

	if (path.size() < 2) return;

	sort(Ex_rainbow_path.begin(), Ex_rainbow_path.end(), path_sorting);

	// 현재 탐색된 보석의 크기
	Block temp = Block(Ex_rainbow_path[0].first, Ex_rainbow_path[0].second, rainbow.size());
	temp.path = path;

	// 더크면 현재 보석으로 교체
	if (temp_size > MAX_size) {
		MAX_size = temp_size;
		big = temp;
	}// 크기가 같으면
	else if(temp_size == MAX_size){
		// 무지개 수가 더 많은 것으로 교체
		if (temp.n_rainbow > big.n_rainbow) {
			big = temp;
		}// 무지개 수가 같으면
		else if (temp.n_rainbow == big.n_rainbow) {
			// 행좌표가 더 큰것으로 교체
			if (temp.x > big.x) {
				big = temp;
			}// 행좌표가 같으면
			else if (temp.x == big.x) {
				// 열좌표가 큰것으로 교체
				if (temp.y > big.y) {
					big = temp;
				}
			}
		}
	}

	// 무지개색은 다음 블럭탐색시 중복방문이 가능함으로 방문표시 해제
	for (int i = 0; i < rainbow.size(); i++) {
		visited[rainbow[i].first][rainbow[i].second] = false;
	}
}

void Delete() {
	// big.path에 저장되어 있는 블럭들 삭제
	for (int i = 0; i < big.path.size(); i++) {
		map[big.path[i].first][big.path[i].second] = -2;
	}
}

void Gravity() {
	for (int j = 0; j < N; j++) {
		for (int i = N - 1; i >= 0; i--) {
			// 검은색은 안움직임
			if (map[i][j] == -1) continue;
			// 빈칸이면
			if (map[i][j] == -2) {
				int idx = i;
				// 바로 위 검은색이 아닌 색상블록을 찾아서
				while (map[idx][j] != -1 && map[idx][j] == -2 && idx>0) idx--;
				if (map[idx][j] != -1) {
					// 위치 교환
					map[i][j] = map[idx][j];
					map[idx][j] = -2;
				}
			}
		}
	}
}

void Rotation() {
	// 테두리 개수 (회전할 사각형 개수)
	int squar_num = N - 2;
	int len = N - 1;
	for (int i = 0; i < squar_num; i++) {
		// 사각형의 시작 좌표와 끝좌표
		int start_x = 0 + i;
		int start_y = 0 + i;
		int end_x = N - 1 - i;
		int end_y = N - 1 - i;
		
		int temp[20];
		// 회전
		for (int k = 0; k < len; k++) temp[k] = map[start_x][start_y + k];
		for (int k = 0; k < len; k++) map[start_x][start_y + k] = map[start_x + k][end_y];
		for (int k = 0; k < len; k++) map[start_x + k][end_y] = map[end_x][end_y - k];
		for (int k = 0; k < len; k++) map[end_x][end_y - k] = map[end_x - k][start_y];
		for (int k = 0; k < len; k++) map[end_x - k][start_y] = temp[k];
		len -= 2;
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	// 기본정보 입력
	cin >> N >> M;
	
	// 맵정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int answer = 0;
	while (true) {
		// 1. 가장 큰 블록 탐색
		memset(visited, false, sizeof(visited));
		big = Block(-1, -1, 0);
		MAX_size = 0;
			// 행이 가장 큰거, 열이 가장 큰거임으로
			// 오른쪽 아래부터 탐색
		for (int i = N-1; i >= 0; i--) {
			for (int j = N-1; j >= 0; j--) {
				// 빈칸이나 검은색은 넘기기
				if (map[i][j] == -2 || map[i][j] == -1) continue;
				// 무지개 거나 이미 방문한 건 넘기기
				if (map[i][j] == 0 || visited[i][j]) continue;
				Bfs(i, j, map[i][j]);
			}
		}

		//printf("가장큰 블록: (%d, %d), 크기: %d\n", big.x, big.y, big.path.size());
		//for (int k = 0; k < big.path.size(); k++) printf("(%d, %d) ", big.path[k].first, big.path[k].second);

		//cout << "초기상태: " << endl;
		//Print();

		// 더이상 탐색되는 보석이 없으면 종료
		if (big.x == -1) break;

		// 2. 보석제거
		answer += (big.path.size() * big.path.size());
		Delete();

		//cout << "보석제거 후: " << endl;
		//Print();

		// 3. 중력작용
		Gravity();

		//cout << "보석제거 후 중력작용: " << endl;
		//Print();

		// 4. 회전
		Rotation();

		//cout << "회전 후: " << endl;
		//Print();

		// 5. 중력작용
		Gravity();

		//cout << "회전 후 중력작용: " << endl;
		//Print();
	}

	cout << answer << endl;

	return 0;
}
