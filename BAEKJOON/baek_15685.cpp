/*
드래곤 커브

다음 세대 = 이전 세대의 이동을 90도 회전한 방향으로 거꾸로 따라감. => stack을 활용

1. 드래곤 커브 완성
  1-1. stak에 경로 저장
  1-2. temp_top을 이용해 이전 세대의 움직임만 tracking
2. 0 ~ 100 (101개의 꼭지점에 대해 4방향이 true면) 개수 ++
*/

#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

// n: 드래곤 커브의 개수
// x, y: 드래곤 커브 시작점
// nx, ny: 드래곤 커브 끝점
// d: 드래곤 커브 방향
// g: 드래곤 커브 세대
// ans: 정사각형 개수
int n, x, y, d, g;
int ans;
int nx, ny;

// 드래곤 커브 경로 저장용 배열 및 인덱스
int top;
int stack[10001];

// 방향 왼, 위, 오, 아
// 회전 공식 next_d = (d + 1) % 4; 
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

// 드래곤 커브 꼭지점 표시
bool map[101][101];

void Make_Dragon_Curve() {
	// 이전 세대 경로 수
	int temp_top = top;

	// 스택에서 꺼내면서 경로 생성
	// 경로 = 스택.pop() + 1 % 4
	while (temp_top != 0) {
		temp_top--;
		int dir = (stack[temp_top] + 1) % 4;
		
		// 다음 지점
		nx = nx + dx[dir];
		ny = ny + dy[dir];

		// 맵에 표시
		map[nx][ny] = true;

		// 경로 저장
		stack[top] = dir;
		top++;
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	memset(map, false, sizeof(map));
	cin >> n;

	for (int i = 0; i < n; i++) {
		//스택 초기화
		top = 0;
		cin >> y >> x >> d >> g; //y가 왼오, x가 위아래

		// 0 세대 생성 및 꼭지점 표시
		map[x][y] = true;
		nx = x + dx[d];
		ny = y + dy[d];
		map[nx][ny] = true;
		
		// 0세대 방향(경로)저장
		stack[top] = d;
		top++;

		// 커브 별 맵에 표시
		for (int j = 0; j < g; j++) {
			Make_Dragon_Curve();
		}
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1]) ans++;
		}
	}

	cout << ans << endl;

	return 0;
}
