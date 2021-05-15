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
