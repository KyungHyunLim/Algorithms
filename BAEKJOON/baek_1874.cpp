#define _CRT_SECURE_NO_WARNINGS
#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<vector>
using namespace std;

int stack[100001];
int top = 0;
vector<char> answer;

int main()
{
	int N;
	scanf("%d", &N);

	int num = 1;

	for (int i = 0; i < N; i++) {
		int temp;
		scanf("%d", &temp);

		while (num <= temp) {
			stack[top++] = num;
			num += 1;
			answer.push_back('+');
		}
		if (stack[top - 1] == temp) {
			stack[--top] = 0;
			answer.push_back('-');
		}
		else {
			printf("NO\n");
			return 0;
		}
	}

	for (int i = 0; i < answer.size(); i++) {
		printf("%c\n", answer[i]);
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}