#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<math.h>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		scanf("%d", &N);

		int sum = 0;
		for (int i = 0; i < N; i++) {
			int temp;
			scanf("%d",&temp);

			sum += temp;
		}

		printf("#%d ", test_case);
		sum == N * (N + 1) / 2 ? printf("Yes\n") : printf("No\n");
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
