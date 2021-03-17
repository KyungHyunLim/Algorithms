#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<math.h>

using namespace std;

int list[26];

int main(int argc, char** argv)
{
	int test_case;
	int T;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(list, 0, sizeof(list));
		
		string s;
		cin >> s;

		for (int i = 0; i < s.size(); i++) {
			list[s[i] - 'a']++;
		}

		printf("#%d ", test_case);

		int count = 0;
		for (int i = 0; i < 26; i++) {
			if (list[i] % 2 != 0) {
				printf("%c", i + 'a');
				count++;
			}
		}

		if (count == 0) printf("Good");

		printf("\n");
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}