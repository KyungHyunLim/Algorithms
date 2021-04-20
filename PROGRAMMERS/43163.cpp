/*
단어 변환

1. 
- 한번에 한자만 변환 가능
- words안에 있는 단어로만 변환 가능
=> word별로 한글자만 다른 글자들 인접리스트 생성

2. dfs를 이용하여 탐색
=> 답이 중간이 아니라 끝까지 가봐야 알수 있으므로 dfs가 적당

*/
#include <string>
#include <vector>

using namespace std;

vector<string> w;

// 인접한 word인지 판단
bool check(string a, string b) {
    int count = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == b[i]) count++;
    }
    // 한글자만 다르면 인접한 word
    if (count == a.length()-1) return true;
    // 아니면 상관 없는 word
    else return false;
}

// word 인접 정보
vector<int> words_map[52];
// 중복 탐색 방지용
bool used[52];
// 최소 변환 횟수
int ans;

void search(int node, int c, string t) {
    // 종료 조건
    // node가 타겟 문자열과 동일하면
    if (w[node] == t) {
        // ans를 최솟값으로 업데이트 하고 종료
        ans = ans > c ? c : ans;
        return;
    }
    else {
        // word 인접 리스트 크기 만큼 반복
        for (int i = 0; i < words_map[node].size(); i++) {
            // 사용된 적이 없는 단어면 진행(최소 횟수 임으로 중복 사용되면 안됨)
            if (used[words_map[node][i]]) continue;
            // 단어 사용됨 표시
            used[words_map[node][i]] = true;
            // 진행
            search(words_map[node][i], c + 1, t);
            // 단어 사용됨 표시 해제
            used[words_map[node][i]] = false;
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    // word별로 한글자만 다른 글자들 인접리스트 생성
    words.push_back(begin);
    // 전역 변수 사용을 위한 대입
    w = words;
    // words안에 target 문자열이 있는지 확인
    bool flag = false;
    for (int i = 0; i < words.size(); i++) {
        // 비교 대상
        string base = words[i];
        // target 문자열이 있으면 true로 변경
        if (words[i] == target) flag = true;
        for (int j = 0; j < words.size(); j++) {
            // 자기자신은 pass
            if (i == j) continue;
            // 인접 word 조건을 만족하면 인접리스트에 추가
            if (check(base, words[j])) words_map[i].push_back(j);
        }
    }

    // words안에 target 문자열이 있으면 진행
    if (flag) {
        ans = 987654321;
        search(words.size() - 1, 0, target);
    }
    // 없으면 0
    else {
        ans = 0;
    }

    return ans;
}

// 디버깅용 
int main() {

    solution("hit", "cog", { "hot", "dot", "dog", "lot", "log", "cog" });

    return 0;
}
