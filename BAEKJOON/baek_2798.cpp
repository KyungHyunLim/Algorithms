#define _CRT_SECURE_NO_WARNINGS
#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<time.h>
using namespace std;

int answer;

//완전탐색
void search(int N, int M, int* arr) {
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (i == j) continue;
			for (int z = j+1; z < N; z++) {
				if (j == z || i == z) continue;
				int sum = arr[i] + arr[j] + arr[z];
				if(sum <= M) answer = MAX(sum, answer);
			}
		}
	}
}

//조합
void combination(int* arr, int M, int N, int amount, int*selected, int i, int next) {
	if (i == amount) {
		int sum = arr[selected[0]] + arr[selected[1]] + arr[selected[2]];
		if (sum <= M) answer = MAX(sum, answer);
		return;
	}

	if (next >= N) return;

	selected[i] = next;
	combination(arr, M, N, amount, selected, i+1, next + 1);
	combination(arr, M, N, amount, selected, i, next + 1);
}

int main()
{
	time_t start, end;

	int N, M;
	scanf("%d %d", &N, &M);

	int arr[101];
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	start = time(NULL);

	//Method 1.
	answer = 0;
	search(N, M, arr);
	printf("%d\n", answer);

	end = time(NULL);
	printf("걸린시간: %lf\n", (double)(end - start));

	start = time(NULL);

	//Method 2.
	answer = 0;
	int selected[3];
	combination(arr, M, N, 3, selected, 0, 0);
	printf("%d\n", answer);

	end = time(NULL);
	printf("걸린시간: %lf\n", (double)(end - start));

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}