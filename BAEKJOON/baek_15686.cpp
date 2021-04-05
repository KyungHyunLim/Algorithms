/*
치킨 배달

0. 치킨집 리스트, 집 리스트, 거리정보 리스트(각 경우마다 중복 연산 방지) 생성
1. combination 만들기
2. 각 경우마다 거리측정 후 ans 업데이트

*/
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

#define MIN(A,B) A<B?A:B
#define INF 987654321

int N, M;
vector<pair<int, int>> chicken;
vector<pair<int, int>> house;
bool selected_chicken[251];
int** d;
int ans;

void combination(int n, int r, int idx, int cnt) {
	if (cnt == r) {
		int sum = 0;
		for (int i = 0; i < house.size(); i++) {
			int dist = INF;
			for (int j = 0; j < chicken.size(); j++) {
				if(selected_chicken[j])
					dist = MIN(dist, d[i][j]);
			}
			if(dist != INF)
				sum += dist;
		}

		ans = MIN(ans, sum);
		return;
	}

	for (int i = idx; i < n; i++) {
		if (selected_chicken[i]) continue;
		selected_chicken[i] = true;
		combination(n, r, i, cnt + 1);
		selected_chicken[i] = false;
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	ans = INF;
	memset(selected_chicken, false, sizeof(selected_chicken));

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (temp == 1) {
				house.push_back(make_pair(i+1, j+1));
			}
			else if (temp == 2) {
				chicken.push_back(make_pair(i+1, j+1));
			}
		}
	}

	//d[house][chicken] : distance of house <-> chicken
	d = (int**)malloc(house.size() * sizeof(int*));
	for (int i = 0; i < house.size(); i++) {
		d[i] = (int*)malloc(chicken.size() * sizeof(int));
		for (int j = 0; j < chicken.size(); j++) {
			d[i][j] = abs(house[i].first - chicken[j].first) + abs(house[i].second - chicken[j].second);
		}
	}

	combination(chicken.size(), M, 0, 0);

	cout << ans << endl;

	return 0;
}
