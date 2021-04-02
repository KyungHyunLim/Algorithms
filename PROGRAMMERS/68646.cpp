/*
월간 코드 챌린지 1
풍선 터트리기

현재 인덱스를 중심으로 자신이 최소값 or 중간 값이 되면은 남는 것이 가능 
==> 왼쪽으로 부터 최솟값 / 오른쪽으로 부터 최솟값 둘중 하나보다 작거나 같으면 가능
*/

#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define _MIN(A,B) A<B?A:B

int left_dp[1000001];
int right_dp[1000001];

int solution(vector<int> a) {
    
    left_dp[0] = a[0];
    right_dp[a.size()-1] = a[a.size()-1];
    for(int i=1; i<a.size(); i++){
        left_dp[i] = min(left_dp[i-1], a[i]);
    }
    for(int i=a.size()-2; i>=0; i--){
        right_dp[i] = min(right_dp[i+1], a[i]);
    }
    
    int answer = 0;
    for(int i=0; i<a.size(); i++){
        if(a[i] <= left_dp[i] || a[i] <= right_dp[i]) answer++;
    }  
    return answer;
}
