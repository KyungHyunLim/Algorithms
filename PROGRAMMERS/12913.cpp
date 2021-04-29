/*
땅따먹기
- 기본적인 DP 문제

d[i][j] = i행에서 j를 선택했을때 최대값

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int d[100000][4];

int solution(vector<vector<int> > land){    
    for(int i=0; i<4; i++){
        d[0][i] = land[0][i];
    }
    
    for(int i=1; i<land.size(); i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<4; k++){
                if(j!=k) d[i][j] = max(d[i][j], d[i-1][k] + land[i][j]);
            }
        }
    }
    
    int answer = 0;
    for(int i=0; i<4; i++){
        answer = max(answer, d[land.size()-1][i]);
    }
    
    return answer;
}
