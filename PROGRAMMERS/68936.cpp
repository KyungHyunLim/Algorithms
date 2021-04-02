/*
월간 코드 챌린지 1
쿼드압축 후 개수 세기

- 분할 정복
- 4개로 사각형 쪼개기
  search(x,  y, next_len);
  search(x,  y+next_len, next_len);
  search(x+next_len,  y, next_len);
  search(x+next_len,  y+next_len, next_len);
*/
#include <string>
#include <vector>

using namespace std;

vector<int> answer;
vector<vector<int>> map;
void search(int x, int y, int length){
    if(length == 1){
        if(map[x][y] == 1) answer[1]++;
        else answer[0]++;
        return;
    }
    int temp_0 = 0;
    int temp_1 = 0;
    for(int i=x; i<x+length; i++){
        for(int j=y; j<y+length; j++){
            if(map[i][j] == 1) temp_1++;
            else temp_0++;
            if(temp_0 > 0 && temp_1 > 0) break;
        }
        if(temp_0 > 0 && temp_1 > 0) break;
    }
    
    if(temp_0 == 0 && temp_1 > 0){
        answer[1]++;
    }else if(temp_1 == 0 && temp_0 > 0){
        answer[0]++;
    }else{
        int next_len = length/2;
        search(x,  y, next_len);
        search(x,  y+next_len, next_len);
        search(x+next_len,  y, next_len);
        search(x+next_len,  y+next_len, next_len);
    }  
}

vector<int> solution(vector<vector<int>> arr) {
    answer.push_back(0);
    answer.push_back(0);
    map = arr;
    search(0, 0, arr.size());
    
    return answer;
}
