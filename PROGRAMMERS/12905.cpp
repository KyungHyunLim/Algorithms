/*
가장 큰 정사각형

브루트 포스 -> 시간초과

Dp 사용!

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;



int solution(vector<vector<int>> board)
{
    int answer = 0;
    int d[1002][1002];
    
    N = board.size();
    M = board[0].size();
    //cout << N << " " << M << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            d[i][j] = board[i][j];
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(board[i][j] == 0) continue;
            d[i][j] = min(d[i-1][j], min(d[i-1][j-1], d[i][j-1])) + 1;
            answer = max(answer, d[i][j]);
        }
    }
  
    return answer*answer;
}
