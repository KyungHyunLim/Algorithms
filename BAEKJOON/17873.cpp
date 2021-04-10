/*
새로운 게임2

0. 데이터 표현
  stack[13][13][11] -> 각 맵위치에 스택 사용(STL X, 배열로 앞뒤로 접근하기 용이하게)
  top[13][13] -> 각 스택의 top 포인터
  map[13][13] -> 각 위치 색 표시 (0 - 흰, 1 - 빨, 2 - 파)
  pieces[10] -> 각 말의 위치 및 방향 정보 표시 ( 1-오, 2-왼, 3-위, 4-아래)
1. 모든 말 이동
  1-1. 움직일 수 없는 경우 거르기 
    1-1.1. 맵밖 / 이동 위치 파랑
    1-1.2. 방향 바꿔서 이동 시도, 다시한번 조건에 걸리면 가만히
    1-1.3. 1.2 로 go 
  1-2. 움직일 수 있는 경우
    1-2.1. 이동 위치 빨강
      1-2.1.1. 이전 위치 스택에서 "이동하는 말 번호 위치 ~ top" 까지 순서대로 새로운 위치 스택에 쌓기
      1-2.1.2. 스택 갱신과 동시에 pieces 갱신 (방향 입력 주의)
    1-2.2. 이동 위치 하양
      1-2.2.1. 이전 위치 스택에서 "top ~ 이동하는 말 번호 위치" 까지 순서대로 새로운 위치 스택에 쌓기
      1-2.2.2. 스택 갱신과 동시에 pieces 갱신 (방향 입력 주의)
2. 턴수 증가
3. 턴수 1000번 넘기거나, 새로운 위치 top >= 4 이면 종료
*/
#include<iostream>
#include<vector>
#include<tuple>
#include<cstring>

using namespace std;

// stack : 각 위치에 쌓일 말 표시
// top : 각 위체에 스택 top 포인터
// map : 각 칸의 색깔 표시
// pieces : 체스말들 정보(위치, 방향)
int stack[13][13][11];
int top[13][13];
int map[13][13];
vector<tuple<int, int, int>> pieces;

// N : 맵크기, K : 체스말 수
int N, K;

// 방향 : 1-오, 2-왼, 3-위, 4-아래
int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, 1, -1, 0, 0};

int change_dir(int d) {
	if (d == 1) return 2;
	else if (d == 2) return 1;
	else if (d == 3) return 4;
	else if (d == 4) return 3;
	return 0;
}

void move(int color, int px, int py, int nx, int ny, int dir, int num) {
	// 흰색일 경우
	if (color == 0) {
		int bottom = 0;
		while (stack[px][py][bottom] != num) bottom++;
		// bottom ~ top 까지 순서대로 옮기면됨
		for (int i = bottom; i < top[px][py]; i++) {
			// 순서대로 옮기기
			if(stack[px][py][i] == num ) pieces[stack[px][py][i]] = make_tuple(nx, ny, dir);
			else pieces[stack[px][py][i]] = make_tuple(nx, ny, get<2>(pieces[stack[px][py][i]]));
			stack[nx][ny][top[nx][ny]++] = stack[px][py][i];
			stack[px][py][i] = 0;
		}
		// 이전 위치 top 업데이트
		top[px][py] = bottom;
	}
	// 빨간 색일 경우
	else if (color == 1) {
		// 이동할 말들 옮기기
		int temp_top = top[px][py];
		while (stack[px][py][top[px][py]] != num) {
			// 이전 위치에서 위에서 부터 하나씩 꺼내
			// 새로운 위치에 넣기
			top[px][py]--;
			if (stack[px][py][top[px][py]] == num) pieces[stack[px][py][top[px][py]]] = make_tuple(nx, ny, dir);
			else pieces[stack[px][py][top[px][py]]] = make_tuple(nx, ny, get<2>(pieces[stack[px][py][top[px][py]]]));
			stack[nx][ny][top[nx][ny]++] = stack[px][py][top[px][py]];
		}

		for (int i = top[px][py]; i < temp_top; i++) {
			stack[px][py][i] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	memset(top, 0, sizeof(top));

	cin >> N >> K;
	// 맵 색깔정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	// 번호 1부터 사용하기 위한 더미 말
	pieces.push_back(make_tuple(-1, -1, -1));
	// 체스말정보 입력
	for (int i = 1; i <= K; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		pieces.push_back(make_tuple(x-1, y-1, d));
		// 스택에 말 번호 넣기
		stack[x-1][y-1][top[x-1][y-1]++] = i;
	}

	int turn = 0;
	bool flag = false;
	// 1000번 넘어 가면 종료
	while (turn <= 1000) {
		for (int i = 1; i<pieces.size(); i++) {
			int x = get<0>(pieces[i]);
			int y = get<1>(pieces[i]);
			int dir = get<2>(pieces[i]);
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			
			// 이동 불가한 경우 거르기
			// 이동할 곳이 맵 밖이거나 파란색이면
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || map[nx][ny] == 2) {
				dir = change_dir(dir);
				nx = x + dx[dir];
				ny = y + dy[dir];
				// 다시한번 걸리면 이동 X
				if (nx < 0 || nx >= N || ny < 0 || ny >= N || map[nx][ny] == 2) {
					pieces[i] = make_tuple(x, y, dir);
					continue;
				}
			}

			// 이제 이동 가능한 경우
			// 말 이동 (색깔, 이동할 위치, 말번호)
			move(map[nx][ny], x ,y, nx, ny, dir, i);

			// 이동한 곳에 말이 4개 이상 되면 종료
			if (top[nx][ny] >= 4) {
				flag = true;
				break;
			}
		}
		turn++;
		if (flag) break;
	}
	
	cout << (turn>1000?-1:turn) << endl;

	return 0;
}
