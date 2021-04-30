/*
행렬 테두리 회전

4개의 반복문을 이용해 회전 

*/
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    // 초기 맵 준비
    int map[101][101];
    int num = 1;
    for(int i=1; i<=rows; i++){
        for(int j=1; j<=columns; j++){
            map[i][j] = num;
            num += 1;
        }
    }
    // 쿼리 실행
    for(int i=0; i<queries.size(); i++){
        int start_x = queries[i][0];
        int start_y= queries[i][1];
        int end_x = queries[i][2];
        int end_y = queries[i][3];
        int temp = map[start_x][end_y];
        
        int _min = min(rows * columns * 2, temp);
        
        // 윗면 회전
        for(int y = end_y; y > start_y; y--) {
            _min = min(_min, map[start_x][y]); // 작은값얻기
            map[start_x][y] = map[start_x][y-1];
        }
        // 왼쪽면 회전
        for(int x = start_x; x < end_x; x++) {
            _min = min(_min, map[x][start_y]); // 작은값얻기
            map[x][start_y] = map[x+1][start_y];
        }
        // 아랫면 회전
        for(int y = start_y; y < end_y; y++){
            _min = min(_min, map[end_x][y]); // 작은값얻기
            map[end_x][y] = map[end_x][y + 1];
        } 
        // 오른쪽면 회전
        for(int x = end_x; x > start_x; x--) {
            _min = min(_min, map[x][end_y]); // 작은값얻기
            map[x][end_y] = map[x-1][end_y];
        }
        // 맨 처음 부분 복원
        map[start_x+1][end_y] = temp;
        answer.push_back(_min); // 작은값 저장
    }        
            
    return answer;
}
