#define _CRT_SECURE_NO_WARNINGS
#define MIN(A,B) A<B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;

int select[3][2] = { {0,1}, {1,2}, {0,2} };
int visited[1010][1010] = { 0, };

void solve(int A, int B, int C, int sum) {
    queue<pair<int,int>> rocks;
    
    //A < B < C;
    if (A > C) { swap(A, C); }
    if (A > B) { swap(A, B); }

    //AB
    rocks.push(make_pair(A, B));
    visited[A][B] = 1;

    //BC
    rocks.push(make_pair(B, C));
    visited[B][C] = 1;

    //AC
    rocks.push(make_pair(A, C));
    visited[A][C] = 1;

    while (!rocks.empty()) {
        int A = rocks.front().first;
        int B = rocks.front().second;
        int C = sum - (A + B);

        int nA = A * 2, nB = B - A;
        if (nA > 1000 || nB > 1000 || C > 1000) continue;
        if (nA <= 0 || nB <= 0 || C <= 0) continue;

        pair<int, int> nK;
        if (nA > nB) {
            if (!select[nB][nA]) {
                select[nB][nA] = 1;
                nK = make_pair(nB, nA);
            }
        }
        else {
            if (!select[nA][nB]) {
                select[nA][nB] = 1;
                nK = make_pair(nA, nB);
            }
        }
        rocks.push(nK);

        if (nA < C) {
            if (!select[nA][C]) {
                select[nA][C] = 1;
                nK = make_pair(nA, C);
            }
        }
        else {
            if (!select[C][nA]) {
                select[C][nA] = 1;
                nK = make_pair(C, nA);
            }
        }
        rocks.push(nK);

        if (nB < C) {
            if (!select[nB][C]) {
                select[nB][C] = 1;
                nK = make_pair(nB, C);
            }
        }
        else {
            if (!select[C][nB]) {
                select[C][nB] = 1;
                nK = make_pair(C, nB);
            }
        }
        rocks.push(nK);
    }
}

int main() {

    int A, B, C;
    cin >> A >> B >> C;

    if ((A + B + C) % 3 != 0) cout << -1;
    else if (A == B && B == C) cout << 1;
    else {
        solve(A, B, C, A+B+C);
        cout << select[(A + B + C) / 3][(A + B + C) / 3];
    }

    return 0;
}

/*
#include <cstdio>
#include <algorithm>
using namespace std;
int A, B, C, sum;
bool visited[1501][1501];

void dfs(int x, int y){
    if (visited[x][y]) return;
    visited[x][y] = true;

    int rock[3] = {x, y, sum - (x + y)};

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (rock[i] < rock[j]){
                int temp[3] = {x, y, sum - (x + y)};
                temp[i] += rock[i];
                temp[j] -= rock[i];
                dfs(temp[0], temp[1]);
            }
        }
    }
}
int main(){
    scanf("%d %d %d", &A, &B, &C);
    sum = A + B + C;

    if (sum % 3 != 0){
        printf("0\n");
        return 0;
    }
    dfs(A, B);

    printf("%d\n", visited[sum / 3][sum / 3]);
    return 0;
}
*/

/*


#include <iostream>

using namespace std;

int gcd(int x, int y){
    if(y==0) return x;
    x%=y;
    return gcd(y,x);
}

int cal_bit(int k){
    int ret=0;
    for(int i=0; i<32; i++){
        ret+=k%2;
        k=k>>1;
    }
    return ret;
}

int main(){
    int A, B, C;
    cin >> A >> B >> C;
    int q=(A+B+C)/(gcd(A, gcd(B,C)));
    cout << (q%3==0 && cal_bit(q/3)==1);
    return 0;
}
*/
/*
세 가지 수가 모두 같은 수가 되려면 어떤 상태인 것인가?

바로 평균 이다.

즉, 세 수의 합이 3의 배수가 아니면 답은 자명하게도 0 이 나와야 한다.

그렇다면 세 수의 합이 3의 배수이면 답은 1 인가?

그렇지는 않다.

해당 문제를 보면 작은 수 X 는 X+X 가 되어 2X 가 되게 되고, 큰 수 Y 는 Y-X 가 된다.

여기서 착안해서 다음과 같은 접근을 할 수 있다.

입력값의 합은 3의 배수여야한다.
입력값들의 최대공약수로 합을 나눴을 때도 3의 배수여야 한다.(1의 계산은 여기서 합쳐진다.)
2에서 계산된 값은 2^k \times 32
k
 ×3 꼴이어야 한다.
어떻게 이런 접근 방법이 나왔을까?

핵심은 X+X=2X, Y-X 가 되면서 다음으로 진행된다는 것이다.

즉, 한 step 마다 수식(또는 인수라고도 생각할 수 있다)에 소인수 2가 추가되는 것이고, 결국 최종적으로 세 수가 같아지는 평균 M에는 몇 개의 소인수 2가 있을 것이다. 즉 2^k2
k
  형태가 되게 된다.
조금 엄밀하게 말하자면, M = 2^k * GM=2
k
 ∗G 의 꼴이 될 것인데, 여기서의 GG 가 바로 최대공약수(gcd) 이다.
*/