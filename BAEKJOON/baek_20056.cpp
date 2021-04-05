/*
마법사 상어와 파이어볼

시뮬레이션 문제 - 주어진 조건에 따라 순차적으로 알고리즘 설계

1. 파이어볼 움직이기
2. 조건에 따라 파이어볼 제거 및 생성
3. 1-2 

*/
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

struct fireball {
	int m; //massive
	int d; //direction
	int s; //speed
	int x;
	int y;

	fireball(int _m, int _d, int _s, int _x, int _y) : 
		m(_m), d(_d), s(_s), x(_x), y(_y) {};
};

int N, M, K;
vector<fireball> f_list;
vector<fireball> map[60][60];

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void Moving() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j].clear();
		}
	}

	for (int i = 0; i < f_list.size(); i++) {
		int x = f_list[i].x;
		int y = f_list[i].y;
		int m = f_list[i].m;
		int s = f_list[i].s;
		int d = f_list[i].d;

		int c = s % N;
		int nx = x + dx[d] * c;
		int ny = y + dy[d] * c;
		if (nx > N) nx -= N;
		if (ny > N) ny -= N;
		if (ny < 1) nx += N;
		if (ny < 1) ny += N;
		f_list[i].x = nx;
		f_list[i].y = ny;
		map[nx][ny].push_back(fireball(m,d,s,nx,ny));

	}
}

void Sum_Massive() {
	vector<fireball> temp;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() == 0) continue;
			if (map[i][j].size() == 1) {
				temp.push_back(map[i][j][0]);
				continue;
			}

			int mass_sum = 0;
			int speed_sum = 0;
			int cnt = map[i][j].size();

			bool even = false;
			bool odd = false;
			for (int k = 0; k < cnt; k++) {
				mass_sum += map[i][j][k].m;
				speed_sum += map[i][j][k].s;
				if (map[i][j][k].d % 2 == 0) even = true;
				else odd = true;
			}

			int mass = mass_sum / 5;
			int speed = speed_sum / cnt;
			if (mass == 0) continue;
			if (even == false || odd == false) {
				int nd[4] = { 0,2,4,6 };
				for (int k = 0; k< 4; k++)
					temp.push_back(fireball(mass, nd[k] ,speed, i, j));
			}
			else {
				int nd[4] = { 1,3,5,7 };
				for (int k = 0; k < 4; k++)
					temp.push_back(fireball(mass, nd[k], speed, i, j));
			}
		}
	}
	f_list = temp;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int m, d, s, x, y;
		cin >> x >> y >> m >> s >> d;
		f_list.push_back(fireball(x, y, m, s, d));
		map[x][y].push_back(fireball(x, y, m, s, d));
	}

	for (int i = 0; i < K; i++) {
		Moving();
		Sum_Massive();
	}

	int ans = 0;
	for (int i = 0; i < f_list.size(); i++) {
		ans += f_list[i].m;
	}

	cout << ans << endl;

	return 0;
}
