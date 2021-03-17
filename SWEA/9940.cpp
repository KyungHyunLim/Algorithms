/*---------------------------------------------------------
순열1.
순열: 1~N 까지 한가지 숫자만 나와야 한다.
- 등차수열의 합 이용.
- 1~N 까지의 합과 실제 입력된 수의 합이 다르면 "NO", 같으면 "YES" 
---------------------------------------------------------*/
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
