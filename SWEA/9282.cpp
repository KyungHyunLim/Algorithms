/*
초콜릿과 건포도.

* 메모이제이션을 이용한 완전탐색.

*/
#include <iostream>
#include <cstring>
#define MAX 1000000000
using namespace std;
  
int dp[51][51][51][51];
int choco[51][51];
int sum[51][51];
  
int solve(int x, int y, int ex, int ey) {
    //초코릿 조각이 한개면 0리턴
    if (x == ex && y == ey) return 0;
    //이미 최솟값을 구해놨으면 최솟값 바로 리턴
    if (dp[x][y][ex][ey] != -1) {
        return dp[x][y][ex][ey];
    }
  
    //(x, y)부터 (ex, ey)까지의 건포도의 합
    int cnt = sum[ex][ey] - sum[x - 1][ey] - sum[ex][y - 1] + sum[x - 1][y - 1];
    int rt = MAX;
  
    //가로로 자르는 경우
    for (int i = x; i < ex; i++) {
        int tmp = solve(x, y, i, ey) + solve(i + 1, y, ex, ey);
        if (rt > tmp + cnt) rt = tmp + cnt;
    }
  
    //세로로 자르는 경우
    for (int i = y; i < ey; i++) {
        int tmp = solve(x, y, ex, i) + solve(x, i + 1, ex, ey);
        if (rt > tmp + cnt) rt = tmp + cnt;
    }
  
    //dp메모하고 리턴
    return dp[x][y][ex][ey] = rt;
}
  
  
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
  
    int T;
    cin >> T;
  
    int n, m;
    for (int tc = 1; tc <= T; tc++) {
        //최솟값 dp배열 -1로 초기화
        memset(dp, -1, sizeof(dp));
         
        cin >> n >> m;  
  
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> choco[i][j];
            }
        }
  
        //누적합
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + choco[i][j];
            }
        }
  
        int ans = solve(1, 1, n, m);
        cout << '#' << tc << ' ' << ans << '\n';
    } 
    return 0;
}
