#define _CRT_SECURE_NO_WARNINGS
#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<queue>
using namespace std;

int q[202];
int front = 0;
int rear = 0;
int max_importance;
queue<int> answer;

void find_max() {
	max_importance = 0;
	for (int i = front; i < rear; i++) {
		max_importance = MAX(max_importance, q[i]);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int test_case = 0; test_case < T; test_case++) {
		int N, M;
		scanf("%d %d", &N, &M);

		front = 0;
		rear = 0;

		max_importance = 0;

		// 중요도 리스트 입력
		for (int i = 0; i < N; i++) {
			scanf("%d", &q[i]);
			rear++;
			max_importance = MAX(max_importance, q[i]);
		}

		//프린트 시작
		int count = 0;
		while (true) {
			//현재 리스트 맨앞의 문서 중요도가 max면 출력
			if (max_importance == q[front]) {
				count++;
				if (front == M) {
					printf("%d\n", count);
					break;
				}
				front++;
				find_max();
				
			}
			//아니면 맨뒤로
			else {
				rear++;
				q[rear-1] = q[front];
				if (front == M) {
					M = rear-1;
				}	
				front++;
			}
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}