/*
보석 쇼핑
*/

//--------------------------------------------------------------------------------------------------------------
/*
map을 이용해
1. 각 보석의 좌표 없데이트
2. 정렬
3. 후보들 저장
4. 후보들 정렬

결과: 효율성 - 시간초과
정확성: 100%, 효율성 0%
*/
//--------------------------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

bool comp(pair<int,int> a, pair<int,int> b){
    if(a.second - a.first < b.second - b.first) return true;
    else if(a.second - a.first == b.second - b.first){
        if(a.first < b.first) return true;
    }
    return false;
}

bool cmp(const pair<string,int>& a, const pair<string,int>& b) {
	return a.second < b.second;
}

vector<int> solution(vector<string> gems) {
    int min_len = 987654321;
    // 보석 종류 개수 구하기
    set<string> gs;
    for(int i=0; i<gems.size(); i++){
        gs.insert(gems[i]);
    }
    // 보석 종류 개수
    int MAX_GEM = gs.size();
    
    map<string, int> info;
    vector<pair<int,int>> candidates;
    int count = 0;
    for(int i=0; i<gems.size(); i++){
        // 현재 보석이 리스트에 없으면 인덱스 저장
        if(info[gems[i]] == 0) {
            info[gems[i]] = i + 1;
            count++;   
        }
        // 좌표에 있으면 갱신
        else{
            info[gems[i]] = i + 1;
        }
        // 보석이 모두 모였으면
        if(count == MAX_GEM ){
            // 보석들의 현재 좌표를 벡터에 삽입
            vector<pair<string,int>> temp(info.begin(), info.end());
            // 정렬을 통해 첫좌표와 끝좌표 구하기
            sort(temp.begin(), temp.end(), cmp);
            // 구간 최소 길이 업데이트
            min_len = min(min_len, temp[temp.size()-1].second - temp[0].second);
            // 현재 최소길이 보다 작으면 후보지에 입력
            if(temp[temp.size()-1].second - temp[0].second <= min_len)
                candidates.push_back(make_pair(temp[0].second, temp[temp.size()-1].second));
        }
    }
    
    // 길이가 작은 순, 좌표가 작은순으로 정렬
    sort(candidates.begin(), candidates.end(), comp);
    
    // 맨첫번째 원소 반환
    return {candidates[0].first, candidates[0].second};
}

//--------------------------------------------------------------------------------------------------------------
/*
후보를 저장하지 않고, 투포인터 인덱스를 활용해 바로바로 업데이트
2-3 과정 삭제

1. 각 보석의 좌표 없데이트

결과: 
정확성: 100%, 효율성 100%
*/
//--------------------------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> gems) {
    int min_len = 987654321;
    // 보석 종류 개수 구하기
    set<string> gs;
    for(int i=0; i<gems.size(); i++){
        gs.insert(gems[i]);
    }
    // 보석 종류 개수
    int MAX_GEM = gs.size();
    
    map<string, int> info;
    // 현재 구입한 보석의 종류 개수
    int count = 0;
    // 후보 시작좌표 및 끝좌표
    int cur_s, cur_e;
    int s_idx = 0, e_idx = 0;
    while(true){
        // 보석의 종류를 전부 구입했으면
        if(count == MAX_GEM ){
            // 구간 길이가 더 작으면 업데이트
            if(e_idx - s_idx < min_len){
                cur_s = s_idx;
                cur_e = e_idx;
                min_len = e_idx - s_idx;
            }
            // 다음 구간으로 슬라이딩
            // 시작 좌표의 보석의 개수가 1보다 많으면
            if(info[gems[s_idx]] > 1){
                // 개수 줄이고, 좌표만 업데이트
                info[gems[s_idx]]--;
                s_idx++;
            }
            else{
                // 1개면, 개수 줄이고, 좌표 업데이트 후
                // 구입 종류 개수 감소
                info[gems[s_idx]]--;
                s_idx++;
                count--;
            }
        }
        // 보석 종류를 모두 구입하지 못한 경우
        else{
            // 끝좌표 도달시 탐색 종료
            if(e_idx == gems.size()) break;
            // 해당 보석이 0개였으면 보석 종류 증가
            if(!info[gems[e_idx]]) count ++;
            // 보석 개수 증가
            info[gems[e_idx]]++;
            // 끝좌표 증가
            e_idx++;
        }
    }
    
    return {cur_s + 1, cur_e};
}
