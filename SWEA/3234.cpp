/*
준환이의 양팔저울

순열 + 가지치기
* 오른쪽에는 왼쪽보다 합이 작을때만 가능
* 남은 추의 합이 왼쪽합보다 작으면 ANSWER + 2^N * N!

*/
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int N;
int sum;
int weights[10];
bool selected[10];
int ans;

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void dfs(int cnt, int l, int r){
	if(cnt == N){
     	ans ++;
        return;
    }
    if(l >= sum - l){
		ans += (pow(2, N-cnt) * factorial(N-cnt));
        return;
    }
    
    for (int i = 0; i < N; i++)
    {
        if (selected[i] == true) continue;
        selected[i] = true;
      
        dfs(cnt + 1, l + weights[i], r);
        if (r + weights[i] <= l) dfs(cnt + 1, l, r + weights[i]);
      
        selected[i] = false;
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        memset(selected, false,sizeof(selected));
        ans = 0;
        sum = 0;
		cin >> N;
        for(int i=0; i<N; i++){
            cin >> weights[i];
            sum += weights[i];
        }
        dfs(0, 0, 0);

        cout << "#" << test_case << " " << ans << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
