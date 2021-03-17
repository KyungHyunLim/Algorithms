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

		// �߿䵵 ����Ʈ �Է�
		for (int i = 0; i < N; i++) {
			scanf("%d", &q[i]);
			rear++;
			max_importance = MAX(max_importance, q[i]);
		}

		//����Ʈ ����
		int count = 0;
		while (true) {
			//���� ����Ʈ �Ǿ��� ���� �߿䵵�� max�� ���
			if (max_importance == q[front]) {
				count++;
				if (front == M) {
					printf("%d\n", count);
					break;
				}
				front++;
				find_max();
				
			}
			//�ƴϸ� �ǵڷ�
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
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}