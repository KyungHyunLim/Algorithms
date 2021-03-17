#define MAX(A,B) A > B ? A : B;
#define MIN(A,B) A < B ? A : B;

#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

struct block {
	int number;
	int area;
	int height;
	int weight;
};

bool compare(block a, block b) {
	return a.weight < b.weight;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	
	vector<block> bl_list;
	block t;
	bl_list.push_back(t);
	for (int i = 1; i <= N; i++) {
		int a, h, w;
		cin >> a >> h >> w;

		block temp;
		temp.number = i;
		temp.height = h;
		temp.area = a;
		temp.weight = w;

		bl_list.push_back(temp);
	}
	
	//무게 기준 정렬
	sort(bl_list.begin(), bl_list.end(), compare);

	//dp
	int dp[101] = {0,};
	dp[0] = 0;
	int max_v = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			if (bl_list[i].area > bl_list[j].area) {
				dp[i] = MAX(dp[i], dp[j] + bl_list[i].height);
				max_v = MAX(dp[i], max_v);
			}
		}
	}

	int index = N;
	vector<int> answer;
	while (index != 0) {
		if (max_v == dp[index]) {
			answer.push_back(bl_list[index].number);
			max_v -= bl_list[index].height;
		}
		index--;
	}
	
	int s = answer.size();
	cout << s << endl;
	for (int i = s-1; i >= 0; i--) {
		cout << answer[i] << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}