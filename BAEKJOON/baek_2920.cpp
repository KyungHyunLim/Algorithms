#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

int main()
{
	int a1;
	scanf("%d", &a1);

	int flag = -1;

	if (a1 == 1) {
		flag = 1;
		for (int i = 2; i < 9; i++) {
			int temp;
			scanf("%d", &temp);
			if (temp != i) flag = 0;
		}
	}
	else if (a1 == 8) {
		flag = 2;
		for (int i = 7; i > 0; i--) {
			int temp;
			scanf("%d", &temp);
			if (temp != i) flag = 0;
		}
	}
	else {
		flag = 0;
	}

	if (flag == 1) printf("ascending");
	else if (flag == 2) printf("descending");
	else printf("mixed");

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}