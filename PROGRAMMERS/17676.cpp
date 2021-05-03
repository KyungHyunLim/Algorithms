/*
2018 Blind 1차 추석 트래픽

1. Log의 시작과 끝시간을 라벨링 해서 하나의 벡터에 삽입
2. 시작 시간기준 정렬, 같으면 시작을 앞으로
3. 벡터를 순회하면서 시작이면 ++, 끝이면 --하면서 최대값 갱신

*/
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// 정렬 기준
bool cmp(pair<int,int> a, pair<int, int> b){
    if(a.first < b.first) return true;
    else if(a.first == b.first) {
        if(a.second < b.second) return true;
    }
    return false;
}

int solution(vector<string> lines) {
    
    vector<pair<int,int>> logs;
    
    for(int i=0; i<lines.size(); i++){
      // string -> ms 단위로 변환
        stringstream sstr(lines[i]);
        string temp; 
        sstr >> temp >> temp; 
        int hh = ((temp[0] - '0') * 10 + (temp[1] - '0')) * 60 * 60 * 1000;  
        int mm = ((temp[3] - '0') * 10 + (temp[4] - '0')) * 60 * 1000; 
        int ss = ((temp[6] - '0') * 10 + (temp[7] - '0')) * 1000; 
        int ms = ((temp[9] - '0') * 100 + (temp[10] - '0') * 10 + (temp[11] - '0')); 
        
        ms += (hh + mm + ss); 
        
        double len; 
        sstr >> len; 
        
      // 벡터에 삽입 시작: 0, 끝: 1
        logs.push_back(make_pair(ms - (int)(len * 1000) + 1, 0)); 
        logs.push_back(make_pair(ms + 999, 1));
    }
    
  // 정렬
    sort(logs.begin(), logs.end(), cmp);
    
    int answer = 0;
    int ans = 0;
  // 벡터 순회
    for(int i=0; i<logs.size(); i++){
        
        //cout << logs[i].first << "\t" << logs[i].second << endl;
        
      // 시작이면 ++
        if(logs[i].second == 0) answer++;
      // 끝이면 --
        else answer--;
      // 최대값 갱신
        ans = max(ans, answer);
    }
    
    return ans;
}
