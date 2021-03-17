#define MIN(A,B) A>B?B:A
#define MAX(A,B) A<B?B:A
#define ll long long
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>

using namespace std;

int N;
ll B, C;
int testroom[1000001];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> testroom[i];
    }
    
    cin >> B >> C;

    ll answer = N;
    for (int i = 0; i < N; i++) {
        ll left = testroom[i] - B;
        answer += left > 0 ? 1 + (left-1)/C : 0;
    }
  
    cout << answer;

    return 0;
}