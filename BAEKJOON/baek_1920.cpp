#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include<iostream>
#include<hash_map>
using namespace std;
using namespace stdext;

int main() {
	
	int N;
	scanf("%d", &N);

	hash_map<int, int> h_table;
	for (int i = 0; i < N; i++) {
		int temp;
		scanf("%d", &temp);
		h_table.insert(hash_map<int,int>::value_type(temp,1));
	}

	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int temp;
		scanf("%d", &temp);
		if (h_table.find(temp) == h_table.end()) printf("%d\n", h_table[temp]);
		else printf("0\n");
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}