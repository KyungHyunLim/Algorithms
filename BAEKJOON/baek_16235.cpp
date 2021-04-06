/*
나무 재테크 

우선 순위 큐 사용 => 시간초과
(priority_queue<pair<int, pair<int, int>>, 
	vector<pair<int, pair<int, int>>>, 
	greater<pair<int, pair<int, int>>>> tree, backup_tree)
  
1. 봄
  1.1 어린 나무 부터 영양분 섭취, 나이증가
  1.2 죽은 나무 리스트 생성
  1.3 번식 나무 리스트 생성
2. 여름
  2.1 죽은 나무 리스트 이용 양분 추가
3. 가을
  3.1 번식 나무 리스트 이용 번식
4. 겨울
  4.1 양분추가
5. 1-4 K번 반복
6. tree.size() 출력

*/
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

#define MAX 11

//tree: 좌표별 트리 목록
	//나이순 입력을 위해 우선순위 큐 사용
//map : 좌표별 양분 량
//basic_map : 겨울에 로봇의 추가를 위해 초기 값 저장
//N: 맵크기, M: 나무수, K: 반복 횟수(년)
priority_queue<pair<int, pair<int, int>>, 
	vector<pair<int, pair<int, int>>>, 
	greater<pair<int, pair<int, int>>>> tree, backup_tree;
int map[MAX][MAX];
int basic_map[MAX][MAX];
int N, M, K;

int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	// 맵에 양분 정보 입력 및 로봇의 추가 양분
	memset(map, 5, sizeof(map));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> basic_map[i][j];
		}
	}

	// 초기 나무 정보 입력
	for (int i = 0; i < M; i++) {
		int x, y, age;
		cin >> x >> y >> age;
		tree.push(make_pair(age,make_pair(x-1,y-1)));
	}

	// K년 동안 반복
	for (int i = 0; i < K; i++) {
		vector<pair<int, pair<int, int>>> dead_tree;
		vector<pair<int, int>> breeding_tree;
		// 봄		
		while (!tree.empty()) { // 나무 목록이 존재하면
			int x = tree.top().second.first;
			int y = tree.top().second.second;
			int age = tree.top().first; // 나무 나이
			tree.pop();
			if (age <= map[x][y]) { // 양분을 섭취할 수 있으면
				map[x][y] -= age; // 양분을 먹은만큼 감소
				backup_tree.push(make_pair(age + 1,make_pair(x, y))); // 나이먹은 나무 새로운 목록에 추가
				if ((age + 1) % 5 == 0) { // 나이가 5의 배수면 번식 가능 목록에 추가
					breeding_tree.push_back(make_pair(x, y));
				}
			}
			else { // 양분을 섭취할 수 없으면
				// 죽은 나무 리스트에 저장
				dead_tree.push_back(make_pair(age, make_pair(x, y)));
			}
		}
		//여름
		for (int j = 0; j < dead_tree.size(); j++) { // 죽은 나무 목록 전체에 대해
			// 각 좌표에 나이/2 만큼의 양분 추가
			map[dead_tree[j].second.first][dead_tree[j].second.second] += (dead_tree[j].first/2);
		}
		//가을
		for (int j = 0; j < breeding_tree.size(); j++) { // 번식 가능한 나무 목록 전체에 대해
			// 8 방위 나이 1인 나무 추가
			for (int k = 0; k < 8; k++) {
				int nx = breeding_tree[j].first + dx[k];
				int ny = breeding_tree[j].second + dy[k];
				// 맵을 벗어나지 않으면
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				// 나이 1인 나무 추가
				backup_tree.push(make_pair(1,make_pair(nx,ny)));
			}
		}
		// 겨울
		// 저장해두었던 초기 양분 값 더하기
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				map[j][k] += basic_map[j][k];
			}
		}
		swap(tree, backup_tree);
	}
	
	// 나무 수 세기
	int answer = tree.size();
	cout << answer << endl;

	return 0;
}
