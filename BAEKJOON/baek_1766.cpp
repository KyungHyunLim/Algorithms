#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int N, M;
	cin >> N >> M;

	priority_queue<int, vector<int>, greater<int>> heap;
	vector<int> answer;
	vector<int> arr[32001];
	int indegree[32001] = { 0, };
	
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;

		arr[x].push_back(y);
		indegree[y] += 1;
	}

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) heap.push(i);
	}

	while (!heap.empty()) {
		int temp = heap.top();
		heap.pop();
		answer.push_back(temp);
		for (int i = 0; i < arr[temp].size(); i++) {
			indegree[arr[temp][i]]--;
			if (indegree[arr[temp][i]] == 0) heap.push(arr[temp][i]);
		}
	}

	for (int i = 0; i < answer.size(); i++) { 
		cout << answer[i]; 
		if (i != answer.size() - 1) cout << " ";
	}
	cout << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}