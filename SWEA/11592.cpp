/*
11592. 크루즈 컨트롤

핵심: TYPE 오차범위 10^-5 신경쓰기 (double 형사용)

가능한 최고속도 = 총 거리 / MAX(총 거리/1번말, 총거리/2번말)
*/

#define MAX(A,B) A>B?A:B
#include<iostream>
#include<vector>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		double D;
		int N;
		double K;
		double S;

		cin >> D >> N;

		double time = -1.0;
		for (int i = 0; i < N; i++) {
			cin >> K >> S;
			time = MAX(time, (D - K) / S);
		}

		double answer = D / time;
		cout << "#" << test_case << " ";
		cout << fixed;
		cout.precision(7);
		cout <<  answer << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
