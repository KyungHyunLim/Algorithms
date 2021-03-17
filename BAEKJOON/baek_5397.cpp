#define _CRT_SECURE_NO_WARNINGS
#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<string.h>

using namespace std;

char LS[1000001];
char RS[1000001];

int main() {
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++) {
		string s;
		cin >> s;

		int LS_top = 0;
		int RS_top = 0;
		memset(LS, '\0', sizeof(LS));
		memset(RS, '\0', sizeof(RS));
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			switch (c) {
			case '-':
				if (LS_top != 0) LS_top--;
				break;
			case '<':
				if (LS_top != 0) {
					char temp = LS[--LS_top];
					RS[RS_top++] = temp;
				}
				break;
			case '>':
				if (RS_top != 0) {
					char temp = RS[--RS_top];
					LS[LS_top++] = temp;
				}
				break;
			default:
				LS[LS_top++] = c;
				break;
			}
		}

		for (int i = 0; i < LS_top; i++) {
			printf("%c", LS[i]);
		}
		for (int i = RS_top-1; i >=0 ; i--) {
			printf("%c", RS[i]);
		}
		printf("\n");
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}




/*
char stack[1000001];
char backup[1000001];
int top = 0;

int main()
{
	int T;
	scanf("%d", &T);

	for (int test = 0; test < T; test++) {
		string s;
		cin >> s;

		int top = 0;
		int cursor = 0;
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			switch (c) {
			case '-':
				if (top != 0) { top--; }
				break;
			case '<':
				if(cursor != 0) cursor--;
				break;
			case '>':
				if (cursor != s.length()-1) cursor++;
				break;
			default:
				if (cursor < top) {
					int index = 0;
					while (cursor != top) {
						backup[index++] = stack[--top];
					}
					stack[top++] = c;
					while (index > 0) {
						stack[top++] = backup[--index];
					}
				}
				else {
					stack[top++] = c;
					cursor = top;
				}
				break;
			}
		}

		for (int i = 0; i < top; i++) {
			printf("%c\n", stack[i]);
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
*/