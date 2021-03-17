#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<map>
using namespace std;

int parent[200002];
int network_size[200002];
char name_f1[21], name_f2[21];
int n;

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

int Union(int x, int y) {
	x = find(x);
	y = find(y);

	if (x != y) {
		parent[x] = y;
		network_size[y] += network_size[x];
		network_size[x] = 1;
	}

	return network_size[y];
}


int main() {
	int T;
	scanf("%d", &T);

	for (int test_case = 0; test_case < T; test_case++) {
		int count = 1;

		map<string, int> friend_set;
		int N;
		scanf("%d", &N);

		for (int i = 0; i <= (2*N); i++) {
			parent[i] = i;
			network_size[i] = 1;
		}

		for (int i = 0; i < N; i++) {
			scanf("%s %s", &name_f1, &name_f2);
			if (friend_set.count(name_f1) == 0) friend_set[name_f1] = count++;
			if (friend_set.count(name_f2) == 0) friend_set[name_f2] = count++;

			printf("%d\n", Union(friend_set[name_f1], friend_set[name_f2]));
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}