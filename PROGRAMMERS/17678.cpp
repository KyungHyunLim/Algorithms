/*
kakao blind 2018 셔틀버스

*** start_time >= info[info_idx], =을 빼먹지 말자....!

1. 문자열 분단위로 변환
2. 오름차순 정렬
3. 마지막 버스까지 탑승 인원 제거 (인덱스 증가)
 3-1. 마지막 버스전에 인원이 0이되면 마지막 버스로 시간 변경
4. 마지막 버스에서 1자리 남기기
 4-1. 남은 크루가 없거나 남은 크루가 출발시간 이후에 오면, 버스 출발 시간에오면 탐승 가능
 4-2. 남은 크루가 있으면, 해당 크루보다 1분 빨리 와야 탑승 가능
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
    
    vector<int> info;
    for(int i=0; i<timetable.size(); i++){
        int temp = stoi(timetable[i].substr(0,2)) * 60 + stoi(timetable[i].substr(3,2));
        info.push_back(temp);
    }
    
    sort(info.begin(), info.end());
    
    int start_time = 9 * 60;
    int bus_idx = 0;
    int info_idx = 0;
    vector<int> bus[10];
    while(true){
        //printf("시작 시간: %d(%d), idx=%d(%d)\n", start_time, n, idx, info[idx]);
        // 버스 횟수 막차남기고 중지
        if(bus_idx >= n-1) break;
        // 태울수 있는 만큼 태우기
        while(start_time >= info[info_idx] && m > bus[bus_idx].size()){
            // 다 태웠으면 중지
            if(info_idx >= info.size()) break;
            info_idx++;
            bus[bus_idx].push_back(info[info_idx]);
            
        }
        // 다 태웠으면 중지
        if(info_idx >= info.size()) break;
        bus_idx++;
        start_time += t;
    }
    
    // 막차가 아니면
    if(bus_idx < n-1){
        while(bus_idx < n-1){
            bus_idx++;
            start_time += t;
        }
    }
    
    // 마지막 한대, 한자리 남기기
    while(start_time >= info[info_idx] && m - 1 > bus[bus_idx].size()){
        info_idx++;
        if(info_idx >= info.size()) break;
        bus[bus_idx].push_back(info[info_idx]);
    }
    
    int con;
    // 남은 크루가 없거나 이제 탈 순서가 출발시간 보다 늦게 오면 => 출발 시각 맞춰 오면 해결
    if(info_idx >= info.size() || info[info_idx] > start_time){
        con = start_time;
    }
    // 남은 크루가 있음, 이제 탈 순서가 막차를 탈 수 있음, 이 순서보다 빨리 와야함.
    // info[info_idx] < start_time
    else{
        con = info[info_idx] - 1;
    }
      
    string answer = "";
    if(con / 60 < 10) answer += ("0" + (to_string(con / 60))); 
    else answer += to_string(con / 60);
    answer += ":"; 
    if(con % 60 < 10) answer += ("0" + (to_string(con % 60))); 
    else answer += to_string(con % 60);
    return answer;
}
