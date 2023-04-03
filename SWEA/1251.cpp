"""
Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

/*
[S/W 문제해결 응용] 4일차 - 하나로

최소신장트리(크루스칼 알고리즘)

1. 간선들 오름차순 정렬
2. 각 정점 부모(그룹 번호)를 자신으로 설정
3. 모든 간선에 대해 부모(그룹 번호)가 다를 때만 간선 선택(사이클 방지)

*/
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

int N;
int set[1001];
double E;
double node[1001][2];

class Edge {
public:
	int node[2];
	double cost;

	Edge(int x, int y, double c) {
		node[0] = x;
		node[1] = y;
		cost = c;
	}
};

bool cmp(Edge a, Edge b) {
	return a.cost < b.cost;
}

// 그룹 얻기 (부모)
int get_parent(int x) {
	if (x == set[x]) return x;
	return set[x] = get_parent(set[x]);
}

// 그룹 통합
void Union(int x, int y) {
	x = get_parent(x);
	y = get_parent(y);
	if (x < y) set[y] = x;
	else set[x] = y;
}

// 같은 그룹인지 확인
bool Find(int x, int y) {
	x = get_parent(x);
	y = get_parent(y);
	if (x == y) return true;
	else return false;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		for (int i = 0; i < N; i++) {
			double x;
			cin >> x;
			node[i][0] = x;
			// 모든 노드 자기자신을 부모로 초기화
			set[i] = i;
		}
		for (int i = 0; i < N; i++) {
			double y;
			cin >> y;
			node[i][1] = y;
		}

		cin >> E;

		vector<Edge> e;
		// 모든 Edge 정보 생성
		for (int i = 0; i < N - 1; i++) {
			for (int j = i + 1; j < N; j++) {
				double cost = pow(sqrt(
					pow(node[i][0] - node[j][0], 2) +
					pow(node[i][1] - node[j][1], 2)),2) * E;
				e.push_back(Edge(i, j, cost));
			}
		}

		// Edge 비용 기준 오름차순 정렬
		sort(e.begin(), e.end(), cmp);

		//모든 간선에 대해 부모가 다를때, 사이클이 발생 안할때 간선 선택
		//오름차순으로 정렬했기 때문에 자동으로 최소 비용이됨
		double ans = 0;
		for (int i = 0; i < e.size(); i++) {
			if (!Find(e[i].node[0], e[i].node[1])) {
				ans += e[i].cost;
				Union(e[i].node[0], e[i].node[1]);
			}
		}
		
		cout << "#" << test_case << " " << (long long)round(ans) << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
