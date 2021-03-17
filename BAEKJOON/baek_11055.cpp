#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int dp[1001];
vector<int> dp_list[1001];
int arr[1001];
int N;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		dp[i] = 1;
		//dp_list[i].push_back(arr[i]);
	}

	if (N == 1) {
		cout << 1 << endl;
		cout << arr[0] << endl;
		return 0;
	}

	int answer = 1;
	dp_list[0].push_back(arr[0]);
	for (int i = 1; i < N; i++) {
		dp_list[i].push_back(arr[i]);
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				if (dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					dp_list[i].clear();
					dp_list[i] = dp_list[j];
					dp_list[i].push_back(arr[i]);
					answer = i;
				}
			}
			
		}
	}

	//int idx;
	//for (int i = 0; i < n; i++) {
	//	int size = dp_list[i].size();
	//	if (size > answer) {
	//		answer = size;
	//		idx = i;
	//	}
	//}

	cout << dp_list[answer].size() << endl;
	for (int i = 0; i < dp_list[answer].size(); i++) {
		cout << dp_list[answer][i];
		if (i != dp_list[answer].size() - 1) cout << " ";
	}
	cout << endl;	
	
	return 0;
}