#include<iostream>
#include<algorithm>
using namespace std;

int arr[200000];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, C;
	int answer = 0;
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr+N);
	
	int start = 1; //min
	int end = arr[N-1] - arr[0]; //max

	while (start <= end) {
		int mid = (start + end) / 2;
		int value = arr[0];
		int count = 1;
		for (int i = 1; i < N; i++) {
			if (arr[i] >= value + mid) {
				value = arr[i];
				count++;
			}
		}
		if (count >= C) {
			start = mid + 1;
			answer = mid;
		}
		else {
			end = mid - 1;
		}
	}

	cout << answer << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}