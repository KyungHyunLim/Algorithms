#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
위상정렬 <Topology Sort> => 순서가 정해진 정렬
큐를 이용한 구현

* DAG (direct acycle graph)에만 적용 가능
* 시작점이 있어야함 -> 사이클이 있으면 적용 불가능

1. 진입 차수가 0인 노드 큐에 삽입
2. 큐에서 노드 꺼냄, 꺼낸 노드 간선 제거
3. 진입 차수 가 0인 노드 큐에 삽입
4. 큐가 빌때까지 2-3 반복
	4.1 모든 노드를 방문하기 전에 큐가 비면 사이클 존재 (불가능)
	4.2 모든 노드 방문 후 종료시 방문 순서가 곧 위상 정렬 순서
*/
int n, inDegree[10];
vector<int> arr[10];

void topologySort() {
	int result[10];
	queue<int> q;

	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0) q.push(i);
	}

	for (int i = 1; i <= n; i++) {
		if (q.empty()) {
			//사이클 발생
			return;
		}
		int top = q.front();
		q.pop();
		result[i] = top;
		for (int i = 0; i < arr[top].size(); i++) {
			int x = arr[top][i];
			if (--inDegree[x] == 0) q.push(x);
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << result[i] << " ";
	}
}


int main() {
	n = 7;
	arr[1].push_back(2);
	arr[1].push_back(5);
	arr[2].push_back(3);
	arr[3].push_back(4);
	arr[4].push_back(6);
	arr[5].push_back(6);
	arr[6].push_back(7);

	inDegree[2]++;
	inDegree[5]++;
	inDegree[3]++;
	inDegree[4]++;
	inDegree[6]++;
	inDegree[6]++;
	inDegree[7]++;

	topologySort();

	return 0;
}
