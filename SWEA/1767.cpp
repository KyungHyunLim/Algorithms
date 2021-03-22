/*
[SW Test 샘플문제] 프로세서 연결하기

1. core 리스트 (가장자리와 붙어있는 코어 제외 연결)
2. core 별 4방향 + 선택 안함 (dfs - 재귀)
 2-1. 모든 core를 순회했으면, 코어가 가장 많이 설치된 경우 이면서 전선의 길이가 가장 짧은 경우 선택
*/

#include<iostream>
#include<vector>
#include <cstring>
using namespace std;

#define MIN(A,B) A<B?A:B
#define INF 12*12 + 1 //최대 맵 크기에 +1

vector<pair<int, int>> core;
int N; //맵 크기
int map[12][12]; // 맵
int max_installed_core;
int min_installed_line;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

void solve(int current_core, int core_count, int installed_core, int installed_line) {
	//모든 코어 순회 완료시
	if (core_count == core.size()) {
		//설치된 코어 개수가 많은 것 선택
		if (installed_core > max_installed_core) {
			max_installed_core = installed_core;
			min_installed_line = installed_line;
		}
		//같으면 설치된 전선 길이가 짧은 것 선택
		else if (installed_core == max_installed_core) {
			min_installed_line = MIN(min_installed_line, installed_line);
		}
		return;
	}
	
	//4방향 전선 설치
	for (int i = 0; i < 4; i++) {
		vector<pair<int, int>> lines;
		bool isOK = false;
		int x = core[current_core].first;
		int y = core[current_core].second;

		//전선 설치 정보 저장
		while (true) {
			//끝에 다달았으면 설치 성공
			if (x == 0 || x == N - 1 || y == 0 || y == N - 1) {
				isOK = true;
				break;
			}

			x += dx[i];
			y += dy[i];

			if (map[x][y] == 0) {
				lines.push_back(make_pair(x, y));
			}
			//설치 불가능이면 그만.
			else {
				break;
			}
		}

		if (isOK) {
			//전선설치 표시
			for (int k = 0; k < lines.size(); k++) {
				map[lines[k].first][lines[k].second] = -1;
			}
			solve(current_core + 1, core_count + 1, installed_core + 1, installed_line + (int)lines.size());
			//전선설치 표시 제거
			for (int k = 0; k < lines.size(); k++) {
				map[lines[k].first][lines[k].second] = 0;
			}
		}
	}

	//현재 코어 선택안하고 넘기기
	solve(current_core + 1, core_count + 1, installed_core, installed_line);
}


int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;

		//map, core 위치 저장
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					//가장자리 코어 제외
					if (i == 0 || j == 0 || i == N - 1 || j == N - 1) continue;
					core.push_back(make_pair(i, j));
				}
			}
		}

		max_installed_core = 0;
		min_installed_line = INF;

		solve(0, 0, 0, 0);

		cout << "#" << test_case << " " << min_installed_line << endl;
		core.clear();
		memset(map, 0, sizeof(map));
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
