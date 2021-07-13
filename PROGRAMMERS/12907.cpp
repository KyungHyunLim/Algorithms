/*
거스름돈

* 전형적인 dp 문제
dp[i] => i원을 만들기 위한 경우의 수

주의점, 화폐단위에 따라 A, B, C가 있을때
각각의 동전만 사용하는 경우
A, B를 사용하는 경우
A, C를 사용하는 경우 ..
다양한 조합이 나올 수 있기 때문에

화폐의 단위를 기준으로 정렬해
작은 동전부터 사용해 만들수 있는 경우의 수를 추가해줌.

*/
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

#define mod 1000000007

using namespace std;

int solution(int n, vector<int> money) {
    // dp[n] = n원을 만들기 위한 경우의 수
    int dp[100000];
    memset(dp, 0, sizeof(dp));
    // 최소크기 화폐를 찾기 위한것
    sort(money.begin(), money.end());
    dp[0] = 1; // 아무것도 사용하지 않는 경우
  
    // 작은 동전 부터 처리
    for(auto mon : money){
        // 최소 값 부터 ~ 원하는 값까지
        for(int i=mon; i<=n; i++){
            // 동전을 사용할 수 있으면 사용
            if(i - mon < 0) continue;
            // i원을 만들기 위해서, i-mon에서 mon을 사용하는 경우를 추가 할 수 있음
            dp[i] = (dp[i] + dp[i-mon])%mod;
        }
    }
    
    /* 확인용
    for(int i=money[0]; i<=n; i++){
        cout << i << " : " << dp[i] << endl;
    }
    */
    return dp[n]%mod;
}
