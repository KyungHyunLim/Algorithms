/*
Dp.연습 등굣길

f(m,n) = mxn 크기의 맵에서 이동할 수 있는 경우의 수

이동은 오른쪽, 아래쪽으로만 가능 하기 때문에
가로, 세로 방향으로 맵이 넓어졌을 때, 추가될 수 있는 경우는 아래-> 오른쪽 / 오른쪽 -> 아래 두경우이다.
*f(m,n) = f(m-1,n) + f(m,n-1)
*/
#include <string>
#include <vector>

#define mod 1000000007
using namespace std;

bool Isin(int a, int b, vector<vector<int>>& puddles){
    for(int i=0; i < puddles.size(); i++){
        if(puddles[i][0] == a && puddles[i][1] == b) return true;
    }
    return false;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    int map[101][101]{};   
    for(int i=1; i <= m; i++){
        for(int j=1; j <= n; j++){
            // (1,1) 부터 시작하므로 왼위 테두리 부분 0
            // 연못이 있는 곳은 못지나 감으로 0
            if(Isin(i, j, puddles)) map[i][j] = 0;
            // 집위치는 1로 설정
            else if(i==1 && j==1) map[1][1] = 1;
            // 아니면 각각 하나 전 규격에서 1가지 방법으로만 진행이 가능
            // 문제 조건에 따라 mod 해주기
            else map[i][j] = (map[i-1][j] % mod + map[i][j-1] % mod) % mod;
        }
    }
        
    // 최종 경우의 수 반환
    return map[m][n];
}
