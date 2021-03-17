#include<iostream>
#include<map>
using namespace std;

//map<int, int> list;
int list[12];
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	int T;
	
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		cin >> N;

		for (int i = 2; i <= 11; i++) {
			list[i] = 4;
		}
		list[10] = 16;

		int sum = 0;
		for (int i = 0; i < N; i++) {
			int temp;
			cin >> temp;

			sum += temp;
			list[temp]--;
		}
		
		cout << "#" << test_case;
		if (sum >= 20) cout << " STOP" << endl;
		else {
			int count1 = 0;
			int count2 = 0;
			//21보다 작거나 같은 수를 만들 수 있는 카드 개수
			for (int i = 2; i <= 11; i++) {
				if(sum + i > 21) count2 += list[i];
				else count1 += list[i];
			}

			count2 >= count1 ? cout << " STOP" << endl : cout << " GAZUA" << endl;;
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
