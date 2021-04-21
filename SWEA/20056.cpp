/*
마법상어와 파이어볼

1. fireball 구조체 사용
2. 파이어볼 움직이기
  2.1 vector map[50][50] 이용
  2.2 이동 후 정보 저장 및 업데이트
3. 2개이상 모인 파이어볼 합치고 나누기
  3.1 map[50][50].size()가 2개 이상인 곳에 대해, 문제에 주어진 조건에 따라 4개의 파이어볼 추가
  3.2 1개면 그대로 추가
  3.3 fb = new_fb로 파이어볼 정보 업데이트
*/

#define _CRT_NO_SECURE_WARNINGS

#include<iostream>
#include<vector>

using namespace std;

// 파이어볼 구조체
struct fireball {
	int m; // 질량
	int d; // 방형
	int s; // 속도
	int r; // 행 위치
	int c; // 열 위치
  // 초기화
	fireball(int m, int d, int s, int r, int c) :
		m(m), d(d), s(s), r(r), c(c) {};
};

// N: 맵크기
// M: 초기 파이어볼 수
// K: 파이어볼 이동 횟수
int N, M, K;

// 파이어볼들 리스트
vector<fireball> fb;

// 파이어볼 중심 8방향
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

// 디버깅용
void print(vector<fireball> ff) {
	for (int i = 0; i < ff.size(); i++) {
		printf("r: %d, c: %d, m: %d, s: %d, d: %d\n", ff[i].r, ff[i].c, ff[i].m, ff[i].s, ff[i].d);
	}
	cout << endl;
	cout << endl;
}

// 파이어볼 이동
void move() {
  // 여러개의 파이어볼이 모이는 것을 표현하기 위한 맵
	vector<int> map[50][50];
	// 파이어볼 이동
	for (int i = 0; i < fb.size(); i++) {
		// 움직일 칸수 = N번 움직이면 자기 자리 그래로 임으로 나머지 연산 사용 (속도 % N)
		int moving_count = (fb[i].s % N);
    // 움직여야 할 만큼 r, c 더하기 (움직일 칸수 * 방향)
		int nx = fb[i].r + moving_count * dx[fb[i].d];
		int ny = fb[i].c + moving_count * dy[fb[i].d];
    // 맵밖을 벗어나면 => 맵끝과 끝이 이어져 있다고 했으므로
    // 아래와 같이 변경
		if (nx < 0) nx = N + nx;
		if (nx >= N) nx = nx - N;
		if (ny < 0) ny = N + ny;
		if (ny >= N) ny = ny - N;
    // 맵에 이동 완료된 파이어볼 넣어주기
		map[nx][ny].push_back(i);
    // 이동된 좌표 업데이트
		fb[i].r = nx;
		fb[i].c = ny;
	}

	// 동일칸 파이어볼 처리
	vector<fireball> new_fb;
  // 모든 맵 칸에 대해서
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int m_sum = 0;
			int s_sum = 0;
			bool flag = true;
			int left;
      // 파이어볼이 여러개면 진행
			if (map[i][j].size() > 1) {
        // 모인 파이어볼의 질량 및 속도합, 방향 정보 구하기
				for (int k = 0; k < map[i][j].size(); k++) {
					left = fb[map[i][j][0]].d % 2;
          // 하나라도 처음과 다른 홀수/짝수 방향이 있으면 false
					if (left != (fb[map[i][j][k]].d % 2)) flag = false;
					m_sum += fb[map[i][j][k]].m;
					s_sum += fb[map[i][j][k]].s;
				}
        // 질량이 0이면 소멸
				if (m_sum / 5 != 0) {
          // 방향 정보에 따라
					if (flag) { // 모두 홀수 || 짝수 이면 0 2 4 6
						new_fb.push_back(fireball(m_sum / 5, 0, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 2, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 4, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 6, s_sum / map[i][j].size(), i, j));
						
					}
					else { // 아니면 1 3 5 7
						new_fb.push_back(fireball(m_sum / 5, 1, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 3, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 5, s_sum / map[i][j].size(), i, j));
						new_fb.push_back(fireball(m_sum / 5, 7, s_sum / map[i][j].size(), i, j));
					}
				}
			}
      // 파이어볼이 하나 밖에 없으면 있는 파이어볼 한개를 new_fb에 삽입
			else if (map[i][j].size() == 1) {
				new_fb.push_back(fb[map[i][j][0]]);
			}
		}
	}
  // 파이어볼 정보 최신화
	fb = new_fb;
	//print(fb);
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;
  
  // 파이어볼 정보입력
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		fb.push_back(fireball(m, d, s, r - 1, c - 1));
	}
  
  // K번 이동
	for (int i = 0; i < K; i++) {
		move();
	}

  // 남은 파이어볼 질량 합 구하기
	int ans = 0;
	for (int i = 0; i < fb.size(); i++) {
		ans += fb[i].m;
	}

	cout << ans << endl;

	return 0;
}
