/*
베스트 앨범

0. 자료구조 준비
  a. map을 이용한 장르 - 곡리스트(재생횟수, 곡번호)  
  b. map을 이용한 장르 - 총 재생횟수
1. 위 두 자료 구조 내림차순 정렬
2. b를 최상위 반복문으로 두고 a를 1개 또는 2개 채움
*/
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

// 장르 - <재생횟수, 번호>
map<string, vector<pair<int,int>>> v;
// 장르 - 재생횟수 총합
map<string, int> sum;

// 장르내에서 내림차순 정리
bool compare(pair<int,int> a, pair<int, int> b) {
    if (a.first > b.first) return true;
    else if (a.first == b.first) {
        if (a.second < b.second) return true;
        else return false;
    }
    return false;
}

// 장르끼리 비교 내림차순 정리
bool compare2(string a, string b) {
    if (sum[a] > sum[b]) return true;
    return false;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    
    // 장르 종류
    set<string> gs;
    // 장르 별 횟수
    for (int i = 0; i < genres.size(); i++) {
        // 장르의 곡별 재생 횟수
        v[genres[i]].push_back(make_pair(plays[i], i));
        // 장르별 총 재생 횟수
        sum[genres[i]] += plays[i];
        // 장르 종류
        gs.insert(genres[i]);
    }
    
    // 장르별 곡 정렬
    set<string>::iterator iter;
    vector<string> gss;
    for (iter = gs.begin(); iter != gs.end(); iter++) {
        // 각 장르에서 재생된 곡들 내림 차순으로 정렬
        sort(v[*iter].begin(), v[*iter].end(), compare);
        // 장르 종류 입력
        gss.push_back(*iter);
    }
    
    // 장르끼리 비교 내림차순 정리
    sort(gss.begin(), gss.end(), compare2);
    
    vector<int> answer;
    // 총 재생횟수가 많은 장르부터
    for (int i = 0; i < gss.size(); i++) {
        if (v[gss[i]].size() == 1){
            answer.push_back(v[gss[i]][0].second);
        }
        else {
            // 2곡씩 수령
            for (int j = 0; j < 2; j++) {
                answer.push_back(v[gss[i]][j].second);
            }
        }
    }
    return answer;
}
